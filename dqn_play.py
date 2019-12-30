# -*- coding: utf-8 -*-

import numpy as np
import gym
import random

from collections import deque
from keras.layers import Input, Activation, Dense, Flatten, RepeatVector, Reshape
from keras.layers.convolutional import Conv2D
from keras.models import Model
from keras import backend as K

import cv2
from skimage.color import rgb2gray
from skimage.transform import resize
# rmsprop
import keras
import __init__

np.set_printoptions(suppress=True)

resize_x = 84
resize_y = 84

file_history = open("history.txt", "w")
file_history.close()


class Agent:
    def __init__(self, env):
        self.env = env
        self.input_dim = env.observation_space.shape
        self.output_dim = env.action_space.n

        self.q_network = self.ModelCreate()
        self.t_network = self.ModelCreate()

        self.t_network.load_weights("weight.h5") # 初期の重みを考慮する場合
        self.q_network.summary()
        self.max_q = 0

    def ModelCreate(self):
        ip = Input(shape=(resize_y, resize_x, 1))
        h = Conv2D(32, (4,4),strides=(2,2),padding="same",activation='relu')(ip)
        h = Conv2D(64,(4,4),strides=(4,4),padding="same",activation='relu')(h)
        h = Conv2D(64,(3,3),strides=(3,3),padding="same",activation='relu')(h)
        h = Flatten()(h)
        h = Dense(512, activation='relu')(h)
        h = Dense(self.output_dim)(h)
        model = Model(ip, output=h)

        rmsprop = keras.optimizers.RMSprop(lr=0.00025, rho=0.95, epsilon=0.01, decay=0.0)
        model.compile(rmsprop, 'mse')
        return model

    def getAction(self, state, epsilon):
        # epsilon-greedy
        if np.random.rand() < epsilon:
            return self.env.action_space.sample()

        state = state[np.newaxis,:,:,:]
        #q_value = self.Predict(state)
        q_value = self.q_network.predict_on_batch(state)
        return np.argmax(q_value)


    def Predict(self, x_batch):
        return self.t_network.predict_on_batch(x_batch)


def Preprocess(image, _resize_x=resize_x, _resize_y=resize_y):
    gray_image = rgb2gray(image)
    gray_image = resize(gray_image, (_resize_x, _resize_y))
    return gray_image[:,:,np.newaxis]

def main():

    env_name = 'myenv-v0'
    env = gym.make(env_name)
    agent = Agent(env)
    replay_memory = deque()

    epsilon=0.05

    state=env.reset()
    state=Preprocess(state,resize_x,resize_y)
    end_flag=False
    while not end_flag:
        action = agent.getAction(state,epsilon)
        end_flag=False
        state2, reward, end_flag, info = env.step(action)
        img=env.render('human')
        cv2.imshow("a",img)
        cv2.waitKey(1)
    env.close()


if __name__ == '__main__':
    main()
