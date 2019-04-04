#       command_center.py     #
# SDC BOOTH 2019 - ATMOSPHERE #
# most be located in directory that also has videos folder

import subprocess, serial, time

def main():
    time.sleep(3)
    while True:
        subprocess.call(['omxplayer', '-o', 'local', ''], cwd='videos/')


if __name__ == '__main__': main()