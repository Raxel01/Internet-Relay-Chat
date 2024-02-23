from  instabot import Bot
import os,shutil 
import time
import sys

Mybot = Bot()
Mybot.login(username="abdelali_ait_talb", password="")

Mybot.follow("deutschlehrerin._")
time.sleep(3)
shutil.rmtree("config")