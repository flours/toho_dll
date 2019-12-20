import ctypes
import numpy as np
import cv2

left=0x25
right=0x27
up=0x26
down=0x28
shift=0x10
shot=ord('Z')
#print(shot)


class toho_env:

    def __init__(self):
        self.libc=ctypes.WinDLL("DLL1\\x64\\Release\\Dll1.dll")
        self.libc.input.restype=None
        self.libc.input.argtype=(ctypes.c_int32*256,)

        self.libc.observe.restype=None
        self.libc.observe.argtype=(ctypes.POINTER(ctypes.c_uint))

        self.img_size=640*480*3
        self.i_arr=[0*self.img_size]
        self.UBYTE_Array=self.img_size*ctypes.c_ubyte
        self.i_arr_c=self.UBYTE_Array(*self.i_arr)



    def main(self):
        self.libc.main()

    def reset(self):
        self.libc.init()

    def observe(self):
        self.libc.observe(self.i_arr_c)
        image=np.ctypeslib.as_array(self.i_arr_c).reshape(480,640,3)
        return image


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

        env.input(mylist)
        env.main()
        image=env.observe()
        mylist=[0]*256
        
        cv2.imshow("aa",image)
        key=cv2.waitKey(1)
        if key==ord('w'):
            mylist[up]=1
        if key==ord('s'):
            mylist[down]=1
        if key==ord('a'):
            mylist[left]=1
        if key==ord('d'):
            mylist[right]=1
        

    print('fulltime',time.time()-start)
