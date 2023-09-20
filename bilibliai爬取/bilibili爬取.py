import json
import os
import time
import subprocess
import re
import requests
import pprint

li_url = ['https://www.bilibili.com/video/BV1Aa411F7Nr', 'https://www.bilibili.com/video/BV1ig411g78q']

headers = {
    'Referer': 'https://www.bilibili.com/',
    'Accept': '*/*',
    'Accept-Language': 'en-US,en;q=0.5',
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.25 Safari/537.36 Core/1.70.3775.400 QQBrowser/10.6.4208.400',
}


def page_conect(url, requests=None):
    response = requests.get(url=url, headers=headers)
    title = re.findall('<title data-vue-meta="true">(.*?)_哔哩哔哩_bilibili</title>', response.text)[0]
    html_data = re.findall('"video":\[{"id":80,"baseUrl":"(.*?)"', response.text)
    html_da2 = re.findall('"audio":\[{"id":30280,"baseUrl":"(.*?)"', response.text)
    print(title + '下载完成')
    # pprint.pprint(response.text)
    video_url = html_data[0]
    audio_url = html_da2[0]
    title = title.replace(' ', '')
    time.sleep(1.5)
    return video_url, audio_url, title


def loan_bili(video_url, audio_url, title):
    # if not os.path.exists('./bili小视频'):
    #     os.mkdir('./bili小视频')
    video_data = requests.get(url=video_url, headers=headers).content
    audio_data = requests.get(url=audio_url, headers=headers).content
    video_path = './bili小视频/' + title + '.mp4'
    audio_path = './bili小视频/' + title + '.mp3'
    with open(video_path, 'wb') as fv:
        fv.write(video_data)
    with open(audio_path, 'wb') as fp:
        fp.write(audio_data)
    return video_path, audio_path


def merge_data(video_name, bro):
    '''使用ffmpeg单个视频音频合并'''
    print("视频合成开始：%s" % video_name)
    outfile_name = './bili小视频/' + video_name + '终极版' + '.mp4'
    cmd = f'E:\\apps\\ffmpeg-4.4-essentials_build\\bin\\ffmpeg -i {bro[1]} -i {bro[0]} -acodec copy -vcodec copy {outfile_name}'
    # print(cmd)
    subprocess.call(cmd, shell=True)
    print("视频合成结束：%s" % video_name)

# for url in li_url:
#     pro = page_conect(url)
#     bro = loan_bili(pro[0],pro[1],pro[2])
#     merge_data(pro[2],bro)
#     time.sleep(2)
#
