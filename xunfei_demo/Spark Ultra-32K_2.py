# coding: utf-8
import _thread as thread
import base64
import json
import ssl
import hmac
import hashlib
from urllib.parse import urlencode, urlparse
from wsgiref.handlers import format_date_time
from datetime import datetime
from time import mktime
import websocket
import os


class Ws_Param:
    def __init__(self, APPID, APIKey, APISecret, gpt_url):
        self.APPID = APPID
        self.APIKey = APIKey
        self.APISecret = APISecret
        self.host = urlparse(gpt_url).netloc
        self.path = urlparse(gpt_url).path
        self.gpt_url = gpt_url

    def create_url(self):
        now = datetime.now()
        date = format_date_time(mktime(now.timetuple()))
        signature_origin = f"host: {self.host}\n"
        signature_origin += f"date: {date}\n"
        signature_origin += f"GET {self.path} HTTP/1.1"

        signature_sha = hmac.new(
            self.APISecret.encode("utf-8"), signature_origin.encode("utf-8"), digestmod=hashlib.sha256
        ).digest()
        signature_sha_base64 = base64.b64encode(signature_sha).decode("utf-8")

        authorization_origin = (
            f'api_key="{self.APIKey}", algorithm="hmac-sha256", headers="host date request-line", signature="{signature_sha_base64}"'
        )
        authorization = base64.b64encode(authorization_origin.encode("utf-8")).decode("utf-8")

        v = {"authorization": authorization, "date": date, "host": self.host}
        return self.gpt_url + "?" + urlencode(v)


def on_message(ws, message):
    data = json.loads(message)
    code = data["header"]["code"]
    if code != 0:
        print(f"请求错误: {code}, {data}")
        ws.close()
    else:
        content = data["payload"]["choices"]["text"][0]["content"]
        print(content, end="")
        if data["payload"]["choices"]["status"] == 2:
            print("\n✅ 生成完毕，连接已关闭。")
            ws.close()


def on_error(ws, error):
    print("❌ 出错：", error)

def on_close(ws, close_status_code, close_msg):
    print("🔚 连接已关闭。", close_status_code, close_msg)



def on_open(ws):
    thread.start_new_thread(run, (ws,))


def run(ws, *args):
    # 生成请求数据
    payload_data = gen_params(
        appid=ws.appid,
        domain=ws.domain,
        question=ws.question,
        image_path=ws.image_path  # 传递图片路径
    )
    data = json.dumps(payload_data, ensure_ascii=False)
    # 打印请求参数（调试用，确认image字段是否正确）
    print("发送的完整请求参数：", data)
    ws.send(data)


def gen_params(appid, domain, question, image_path=None):
    image_base64 = None
    # 读取图片并转为base64
    if image_path and os.path.exists(image_path):
        try:
            with open(image_path, "rb") as f:
                image_base64 = base64.b64encode(f.read()).decode("utf-8")
            print(f"图片编码成功，长度：{len(image_base64)}")
        except Exception as e:
            print(f"图片读取失败：{e}")
    else:
        print(f"图片路径不存在或错误：{image_path}")

    # 严格按讯飞4.0Ultra模型要求构建参数
    data = {
        "header": {
            "app_id": appid,
            "uid": "1234"  # 可自定义，保持固定即可
        },
        "parameter": {
            "chat": {
                "domain": domain,  # 必须是"4.0Ultra"
                "temperature": 0.5,
                "max_tokens": 4096
            }
        },
        "payload": {
            "message": {
                "text": [  # 文字部分：仅包含角色和问题
                    {"role": "user", "content": question}
                ],
                "image": []  # 图片部分：初始为空列表
            }
        }
    }

    # 若图片编码成功，添加到image字段（关键步骤）
    if image_base64:
        data["payload"]["message"]["image"] = [{"data": image_base64}]

    return data




def main(appid, api_secret, api_key, Spark_url, domain, question, image_path=None):
    image_base64 = None
    if image_path and os.path.exists(image_path):
        try:
            with open(image_path, "rb") as f:
                image_base64 = base64.b64encode(f.read()).decode("utf-8")
            # 新增调试：打印编码长度（正常图片的编码长度应大于1000）
            print(f"图片编码成功，长度：{len(image_base64)}")
        except Exception as e:
            print(f"图片读取失败：{e}")  # 捕获读取错误（如权限问题）
    else:
        print(f"图片路径不存在或为空：{image_path}")  # 路径错误提示
    wsParam = Ws_Param(appid, api_key, api_secret, Spark_url)
    wsUrl = wsParam.create_url()

    websocket.enableTrace(False)
    ws = websocket.WebSocketApp(
        wsUrl, on_message=on_message, on_error=on_error, on_close=on_close, on_open=on_open
    )
    ws.appid = appid
    ws.domain = domain
    ws.question = question
    ws.image_path = image_path  # 保存图片路径
    ws.run_forever(sslopt={"cert_reqs": ssl.CERT_NONE})


if __name__ == "__main__":
    main(
        appid="0a9a1587",
        api_secret="MTk2NzZlMmQ2NjE5OTQyYzBiYmZhYzQ4",
        api_key="fcee1a8ab3af7a2a57a2e95451b227c5",
        Spark_url="wss://spark-api.xf-yun.com/v4.0/chat",
        domain="4.0Ultra",
        question="请描述这张图片的内容。",
        image_path="D:/cat.jpg",
    )
