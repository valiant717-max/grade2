# -*- coding:utf-8 -*-
import hashlib
import base64
import hmac
import time
import random
from urllib.parse import urlencode
import json
import requests
from requests_toolbelt.multipart.encoder import MultipartEncoder


class Document_Repo:
    def __init__(self, APPId, APISecret, timestamp):
        self.APPId = APPId
        self.APISecret = APISecret
        self.Timestamp = timestamp

    def get_origin_signature(self):
        m2 = hashlib.md5()
        data = bytes(self.APPId + self.Timestamp, encoding="utf-8")
        m2.update(data)
        checkSum = m2.hexdigest()
        return checkSum

    def get_signature(self):
        # 获取原始签名
        signature_origin = self.get_origin_signature()
        # 使用加密键加密文本
        signature = hmac.new(self.APISecret.encode('utf-8'), signature_origin.encode('utf-8'),
                             digestmod=hashlib.sha1).digest()
        # base64密文编码
        signature = base64.b64encode(signature).decode(encoding='utf-8')
        return signature

    def get_header(self):
        signature = self.get_signature()
        header = {
            "appId": self.APPId,
            "timestamp": self.Timestamp,
            "signature": signature,
        }
        return header


if __name__ == '__main__':
    # 先去 开放平台控制台（https://console.xfyun.cn）创建应用，获取下列应用信息进行替换
    APPId = "0a9a1587"
    APISecret = "MTk2NzZlMmQ2NjE5OTQyYzBiYmZhYzQ4"

    curTime = str(int(time.time()))

    document_Repo = Document_Repo(APPId, APISecret, curTime)
    headers = document_Repo.get_header()


    ###############################知识库创建接口#########################################

    # request_url = "https://chatdoc.xfyun.cn/openapi/v1/repo/create"
    # body = {
    #       "repoName":  "",
    #       "repoDesc": "",
    #       "repoTags":  "",
    # }
    # response = requests.post(request_url, json=body, headers=headers)
    #
    # print("请求头", response.request.headers, type(response.request.headers))
    # print('onMessage：\n' + response.text)

    ################################添加文件##############################################

    # request_url = "https://chatdoc.xfyun.cn/openapi/v1/repo/file/add"
    # body = {
    #     "repoId": "",
    #     "fileIds": [
    #         ""
    #     ]
    # }
    #
    # response = requests.post(request_url, json=body, headers=headers)
    # print("请求头", response.request.headers, type(response.request.headers))
    # print('onMessage：\n' + response.text)

    ########################################知识库列表#############################################

    # request_url = "https://chatdoc.xfyun.cn/openapi/v1/repo/list"
    # body = {
    #     "repoName": "",
    #     "currentPage": 1,
    #     "pageSize": 10
    # }
    #
    # response = requests.post(request_url, json=body, headers=headers)
    # print("请求头", response.request.headers, type(response.request.headers))
    # print('onMessage：\n' + response.text)

    #######################################知识库详情##############################################

    #     request_url = "https://chatdoc.xfyun.cn/openapi/v1/repo/info"
    #     body = {
    #        "repoId": ""
    # }
    #     response = requests.post(request_url, data=body, headers=headers)
    #     print("请求头", response.request.headers, type(response.request.headers))
    #     print('onMessage：\n' + response.text)

    ##################################知识库文件列表###################################################

    #    request_url = "https://chatdoc.xfyun.cn/openapi/v1/repo/file/list"
    #    body = {
    #        "repoId": "",
    #        "fileName": "",
    #        "extName": "",
    #        "currentPage": 1,
    #        "pageSize": 10
    # }
    #    response = requests.post(request_url, json=body, headers=headers)
    #    print("请求头", response.request.headers, type(response.request.headers))
    #    print('onMessage：\n' + response.text)

    ########################################移除文件###################################################

    # request_url = "https://chatdoc.xfyun.cn/openapi/v1/repo/file/remove"
    # body = {
    #       "repoId": "",
    #       "fileIds":  [
    #           "",
    #           ""
    #       ]
    # }
    # response = requests.post(request_url, json=body, headers=headers)
    # print("请求头", response.request.headers, type(response.request.headers))
    # print('onMessage：\n' + response.text)

    ########################################知识库删除##############################################

    # request_url = "https://chatdoc.xfyun.cn/openapi/v1/repo/del"
    # body = {
    #   "repoId": "",
    # }
    # response = requests.post(request_url, data=body, headers=headers)
    # print("请求头", response.request.headers, type(response.request.headers))
    # print('onMessage：\n' + response.text)
