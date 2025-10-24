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

class Document_Upload:
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
        #print(signature)
        header = {
            "appId": self.APPId,
            "timestamp": self.Timestamp,
            "signature": signature,
        }
        return header

    # 提交网络文件
    def get_body(self):
        body = {
            "file": "",
            "url": "http://xingh.dsd.xss/e-0867bed7d1a3/c5a58172-8c1c-4c79-90e0-de4042ba876d1691741866951.txt",
            "fileName": "c5a58112313876d1691741866951.txt",
            "fileType": "wiki",
            "callbackUrl": "your_callbackUrl"
        }
        form = MultipartEncoder(
            fields=body,
            boundary='------------------' + str(random.randint(1e28, 1e29 - 1))
        )
        return form


if __name__ == '__main__':
    APPId = "0a9a1587"
    APISecret = "MTk2NzZlMmQ2NjE5OTQyYzBiYmZhYzQ4"
    curTime = str(int(time.time()))

    document_upload = Document_Upload(APPId, APISecret, curTime)
    headers = document_upload.get_header()

    # ********************1、文档上传************************

    request_url = "https://chatdoc.xfyun.cn/openapi/v1/file/upload"

    # 提交本地文件
    body = {
        "url": "",
        "fileName": "背影.txt",
        "fileType": "wiki",
        "needSummary": False,
        "stepByStep": False,
        "callbackUrl": "your_callbackUrl",
    }
    files = {'file': open('背影.txt', 'rb')}

    response = requests.post(request_url, files=files, data=body, headers=headers)
    print("请求头", response.request.headers, type(response.request.headers))
    print('onMessage：\n' + response.text)

    # 提交网络文件
    # body = document_upload.get_body()
    # headers['Content-Type'] = body.content_type
    # response = requests.post(request_url, data=body, headers=headers)

    # 文档上传成功

    # ******************2、文档切分*******************************

    # request_url = "https://chatdoc.xfyun.cn/openapi/v1/file/split"
    # # 切分符
    # # chunkSeparators = base64.b64encode(json.dumps(";").encode('utf-8'))
    # body = {
    #     "splitType": "wiki",
    #     "isSplitDefault": False,
    #     "fileIds": [
    #         ""    #请填写文档id
    #     ],
    #     "wikiSplitExtends": {
    #         "chunkSeparators": ['DQo='],
    #         "minChunkSize": 100,
    #         "chunkSize": 2000
    #     }
    # }
    #
    # response = requests.post(request_url, json=body, headers=headers)
    # print("请求头", response.request.headers, type(response.request.headers))
    # print('onMessage：\n' + response.text)

    # 文档切分完成

    # ******************3、文档向量化*******************************
    # request_url = "https://chatdoc.xfyun.cn/openapi/v1/file/embedding"
    #
    # body = {
    #     "fileIds": [
    #         ""    #请填写文档id
    #     ]
    # }
    #
    # response = requests.post(request_url, data=body, headers=headers)
    # print("请求头", response.request.headers, type(response.request.headers))
    # print('onMessage：\n' + response.text)

    # 文档向量化完成

    # ******************4、文档状态查询*******************************

    # request_url = "https://chatdoc.xfyun.cn/openapi/v1/file/status"
    #
    # body = {
    #     "fileIds": [
    #         ""    #请填写文档id
    #     ]
    # }
    #
    # response = requests.post(request_url, data=body, headers=headers)
    # print("请求头", response.request.headers, type(response.request.headers))
    # print('onMessage：\n' + response.text)

    # 文档状态查询完成

    # ******************5、文档内容检索*******************************
    # request_url = "https://chatdoc.xfyun.cn/openapi/v1/vector/search"
    #
    # body = {
    #     "fileIds": [""],  #请填写文档id
    #     "content": "",
    #     "chatExtends":{
    #         "wikiFilterScore": 0.82,
    #         "esFilterScore": 10
    #     }
    # }
    # print(headers)
    # response = requests.post(request_url, json=body, headers=headers)
    # print("请求头", response.request.headers, type(response.request.headers))
    # print('onMessage：\n' + response.text)

    # 文档内容检索完成

    # ******************6、文件分块内容*******************************
    # request_url = "https://chatdoc.xfyun.cn/openapi/v1/file/chunks"
    # body = {
    #     "fileId": ""  #请填写文档id
    # }
    # #print(headers)
    # response = requests.post(request_url, data=body, headers=headers)
    # print("请求头", response.request.headers, type(response.request.headers))
    # print('onMessage：\n' + response.text)

    # 文件分块查询完成

    # ******************7、文档总结查询*******************************
    # request_url = "https://chatdoc.xfyun.cn/openapi/v1/file/summary/query"
    # body = {
    #     "fileId": ""  #请填写文档id
    # }
    # # print(headers)
    # response = requests.post(request_url, data=body, headers=headers)
    # print("请求头", response.request.headers, type(response.request.headers))
    # print('onMessage：\n' + response.text)

    # 文档总结查询完成

    # ******************8、文档总结发起*******************************
    # request_url = "https://chatdoc.xfyun.cn/openapi/v1/file/summary/start"
    # body = {
    #     "fileId": ""  #请填写文档id
    # }
    # # print(headers)
    # response = requests.post(request_url, data=body, headers=headers)
    # print("请求头", response.request.headers, type(response.request.headers))
    # print('onMessage：\n' + response.text)

    # 文档总结发起完成

    # ******************9、查询文件详情*******************************
    # request_url = "https://chatdoc.xfyun.cn/openapi/v1/file/info"
    # body = {
    #     "fileId": "c6c4e23c56e84fdca5342c1b553ff82b"  #请填写文档id
    # }
    # # print(headers)
    # response = requests.post(request_url, data=body, headers=headers)
    # print("请求头", response.request.headers, type(response.request.headers))
    # print('onMessage：\n' + response.text)

    # 查询文件详情结束

    #******************10、查询appId下的文档列表*******************************
    # request_url = "https://chatdoc.xfyun.cn/openapi/v1/file/list"
    # body = {
    #     #"fileName": "背影",    #模糊查询
    #     #"extName": "TXT",
    #     #"currentPage": 1,
    #     #"pageSize": 10
    # }
    # # print(headers)
    # response = requests.post(request_url, json=body, headers=headers)
    # print("请求头", response.request.headers, type(response.request.headers))
    # print('onMessage：\n' + response.text)

    # 查询appId下的文档列表结束

    # ******************11、文档删除*******************************
    # request_url = "https://chatdoc.xfyun.cn/openapi/v1/file/del"
    # body = {
    #     "fileIds": [
    #         ""    #请填写文档id
    #     ]
    # }
    # # print(headers)
    # response = requests.post(request_url, data=body, headers=headers)
    # print("请求头", response.request.headers, type(response.request.headers))
    # print('onMessage：\n' + response.text)

    # 文档删除完成