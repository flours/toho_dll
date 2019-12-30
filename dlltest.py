import ctypes
import numpy as np
import cv2
import gym
import gym.spaces

left=0x25
right=0x27
up=0x26
down=0x28
shift=0x10
shot=ord('Z')
#print(shot)


class toho_env(gym.Env):

    def __init__(self):
        self.action_space = gym.spaces.Discrete(9)  # 東西南北
        self.observation_space = gym.spaces.Box(
            low=0,
            high=255,
            shape=(640,480)
            )
        self.reward_range=[-1.,1.]
        self.libc=ctypes.WinDLL("DLL1\\x64\\Release\\Dll1.dll")
        self.libc.input.restype=None
        self.libc.input.argtype=(ctypes.c_int32*256,)

        self.life_pointer=ctypes.c_int(0)
        self.reward_pointer=ctypes.c_int(0)
        self.done_pointer=ctypes.c_int(0)

        self.libc.observe.restype=None
        self.libc.observe.argtype=(ctypes.POINTER(ctypes.c_uint),ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int))

        self.img_size=640*480*3
        self.i_arr=[0*self.img_size]
        self.UBYTE_Array=self.img_size*ctypes.c_ubyte
        self.i_arr_c=self.UBYTE_Array(*self.i_arr)

        self.action=[[],[left],[left,up],[up],[right,up],[right],[right,down],[down],[left,down]]

    def _step(self, action):
        mylist=[0]*256
        for key in self.action[action]:
            mylist[key]=1
        self.input(mylist)
        self.main()
        return self.observe()
    def _reset(self):
        self.libc.init()
        self.libc.reset()
        self._step(0)
        return self.observe()[0]
    def _render(self, mode='human', close=False):
        image=self.observe()
        return image[0]
    def _close(self):
        pass
    def _seed(self, seed=None):
        pass



    def main(self):
        self.libc.main()


    def observe(self):
        self.libc.observe(self.i_arr_c,ctypes.pointer(self.reward_pointer),ctypes.pointer(self.life_pointer),ctypes.pointer(self.done_pointer))
        image=np.ctypeslib.as_array(self.i_arr_c).reshape(480,640,3)
        return image,self.reward_pointer.value,self.done_pointer.value,None


    def input(self,key_list):
        n=np.array(key_list)

        c = n.ctypes.data_as(ctypes.POINTER(ctypes.c_uint8 * n.shape[0])).contents
        self.libc.input(c)


if __name__=='__main__':
    env=toho_env()
    env.reset()
    mylist=[0]*256
    import time

    start=time.time()


    for i in range(10000):
        if i%1000==0:
            env.reset()

        env.input(mylist)
        env.main()
        image=env.observe()
        mylist=[0]*256

        cv2.imshow("aa",image[0])
        key=cv2.waitKey(1)
        print(image[1:])
        if key==ord('w'):
            mylist[up]=1
        if key==ord('s'):
            mylist[down]=1
        if key==ord('a'):
            mylist[left]=1
        if key==ord('d'):
            mylist[right]=1


    print('fulltime',time.time()-start)
