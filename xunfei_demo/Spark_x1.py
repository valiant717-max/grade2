# -*- coding: utf-8 -*-
# ===========================================
# 调用讯飞星火大模型（WebSocket 版本）
# 支持多轮对话（保留历史）
# ===========================================

# ----------- 导入必要模块 -----------
import _thread as thread   # 启动新线程
import base64              # 编码（部分鉴权步骤需要）
import datetime
import hashlib              # 用于生成签名
import hmac                 # 用于HMAC-SHA256加密
import json                 # 用于数据转JSON字符串
from urllib.parse import urlparse, urlencode  # 用于解析URL、拼接参数
import ssl                  # 用于WebSocket安全连接
from datetime import datetime
from time import mktime
from wsgiref.handlers import format_date_time # 格式化HTTP标准时间
import websocket            # WebSocket 客户端库（需安装：pip install websocket-client）

# ----------- 全局变量 -----------
answer = ""                # 存放模型回复的最终内容
isFirstcontent = False     # 是否第一次接收到思维链（reasoning_content）

# ===========================================
# 一、定义鉴权类，生成带签名的 WebSocket 连接地址，生成鉴权URL
# ===========================================
class Ws_Param(object):
    # 初始化函数
    def __init__(self, APPID, APIKey, APISecret, Spark_url):
        """
        参数说明：
        APPID, APIKey, APISecret：在讯飞开放平台控制台获取
        Spark_url：模型接口地址，例如 "wss://spark-api.xf-yun.com/v1/x1"
        """
        self.APPID = APPID
        self.APIKey = APIKey
        self.APISecret = APISecret
        self.host = urlparse(Spark_url).netloc   # 提取主机名（如 spark-api.xf-yun.com）
        self.path = urlparse(Spark_url).path     # 提取路径部分（如 /v1/x1）
        self.Spark_url = Spark_url

    # 生成带鉴权参数的完整请求URL
    def create_url(self):

        now = datetime.now()
        date = format_date_time(mktime(now.timetuple()))

        # 拼接签名字符串（按固定格式）
        signature_origin = "host: " + self.host + "\n"
        signature_origin += "date: " + date + "\n"
        signature_origin += "GET " + self.path + " HTTP/1.1"

        # 使用HMAC-SHA256算法加密签名原文
        signature_sha = hmac.new(
            self.APISecret.encode('utf-8'),
            signature_origin.encode('utf-8'),
            digestmod=hashlib.sha256
        ).digest()

        # 将加密结果转成base64字符串
        signature_sha_base64 = base64.b64encode(signature_sha).decode('utf-8')

        # 拼接authorization字段
        authorization_origin = (
            f'api_key="{self.APIKey}", algorithm="hmac-sha256", '
            f'headers="host date request-line", signature="{signature_sha_base64}"'
        )

        # 再次base64编码整个authorization内容
        authorization = base64.b64encode(authorization_origin.encode('utf-8')).decode('utf-8')

        # 组合成完整URL参数字典
        v = {
            "authorization": authorization,
            "date": date,
            "host": self.host
        }

        # 拼接成最终完整连接URL
        url = self.Spark_url + '?' + urlencode(v)
        return url


# ===========================================
# 二、WebSocket回调函数,定义连接建立、消息接收、错误、关闭时的行为
# ===========================================

# 发生错误时调用
def on_error(ws, error):
    print("### error:", error)

# 连接关闭时调用
def on_close(ws, one, two):
    print("🔚 WebSocket 连接已关闭")

# 连接建立时调用（启动新线程发送数据）
def on_open(ws):
    # 使用_thread模块异步调用 run() 函数，避免阻塞
    thread.start_new_thread(run, (ws,))


# ===========================================
# 三、核心函数：建立连接后向模型发送请求
# ===========================================
def run(ws, *args):
    """
    WebSocket连接建立成功后执行，发送请求内容
    """
    # 生成JSON请求数据
    data = json.dumps(gen_params(appid=ws.appid, domain=ws.domain, question=ws.question))
    # 通过WebSocket发送
    ws.send(data)


# ===========================================
# 接收并处理模型返回的消息（打印思维链 + 内容）
# ===========================================
def on_message(ws, message):
    """
    当WebSocket收到模型返回的消息时触发
    """
    data = json.loads(message)   # 解析为字典
    code = data['header']['code']  # 取返回码

    if code != 0:
        # code != 0 表示接口调用出错
        print(f'请求错误: {code}, {data}')
        ws.close()
    else:
        # 正常返回
        choices = data["payload"]["choices"]
        status = choices["status"]       # 0处理中，2代表回答完毕
        text = choices['text'][0]        # 获取返回的第一段内容
        content = ''

        # 如果返回了思维链（reasoning_content）
        if 'reasoning_content' in text and text['reasoning_content']:
            reasoning_content = text["reasoning_content"]
            print(reasoning_content, end="")
            global isFirstcontent
            isFirstcontent = True

        # 输出模型正式回复内容
        if 'content' in text and text['content']:
            content = text["content"]
            if isFirstcontent:
                print("\n*******************以上为思维链内容，模型回复内容如下********************\n")
            print(content, end="")
            isFirstcontent = False

        global answer
        answer += content  # 拼接所有内容为完整回答

        # status==2 表示已结束
        if status == 2:
            ws.close()


# ===========================================
# 五.生成请求JSON数据，构造发送给星火的请求数据结构
# ===========================================
def gen_params(appid, domain, question):
    """
    根据输入问题生成请求参数JSON
    """
    data = {
        "header": {
            "app_id": appid,
            "uid": "1234",  # 可自定义用户ID
        },
        "parameter": {
            "chat": {
                "domain": domain,       # 模型版本，如"x1"或"4.0Ultra"
                "temperature": 1.2,     # 控制输出随机性
                "max_tokens": 32768     # 控制生成文本长度上限
            }
        },
        "payload": {
            "message": {
                "text": question        # 对话历史或问题
            }
        }
    }
    return data


# ===========================================
# 六、主入口函数，主逻辑：建立连接、绑定回调、启动通讯。
# ===========================================
def main(appid, api_key, api_secret, Spark_url, domain, question):
    """
    建立WebSocket连接并与星火模型交互
    """
    wsParam = Ws_Param(appid, api_key, api_secret, Spark_url)  # 创建鉴权对象
    websocket.enableTrace(False)  # 关闭详细调试信息
    wsUrl = wsParam.create_url()  # 获取完整连接地址

    # 创建 WebSocket 客户端对象，并绑定事件回调函数
    ws = websocket.WebSocketApp(
        wsUrl,
        on_message=on_message,
        on_error=on_error,
        on_close=on_close,
        on_open=on_open
    )
    # 动态给 WebSocket 添加自定义属性
    ws.appid = appid
    ws.question = question
    ws.domain = domain

    # 开始运行（sslopt关闭证书验证）
    ws.run_forever(sslopt={"cert_reqs": ssl.CERT_NONE})


# ===========================================
# 七、对话上下文管理，保存历史问答，实现多轮对话
# ===========================================
text = []  # 保存整个对话历史


def getText(role, content):
    """保存每次对话（用户或助手）的内容到列表"""
    jsoncon = {"role": role, "content": content}
    text.append(jsoncon)
    return text


def getlength(text):
    """计算历史对话内容的总长度"""
    length = 0
    for content in text:
        length += len(content["content"])
    return length


def checklen(text):
    """
    检查对话是否超出长度限制（8000字符）
    若超过则删除最早的记录
    """
    while getlength(text) > 8000:
        del text[0]
    return text


# ===========================================
# 八、程序主入口
# ===========================================
if __name__ == '__main__':
    # === 请在讯飞开放平台控制台中获取以下信息 ===
    appid = "0a9a1587"
    api_secret = "MTk2NzZlMmQ2NjE5OTQyYzBiYmZhYzQ4"
    api_key = "fcee1a8ab3af7a2a57a2e95451b227c5"

    # 选择使用的模型版本
    domain = "x1"  # “x1”为最新版本，官方建议使用
    Spark_url = "wss://spark-api.xf-yun.com/v1/x1"  # WebSocket接口地址

    # === 主循环 ===
    while True:
        Input = input("\n我: ")           # 用户输入
        question = checklen(getText("user", Input))  # 加入历史
        print("星火:", end="")           # 打印提示
        main(appid, api_key, api_secret, Spark_url, domain, question)
        getText("assistant", answer)     # 保存模型回复到历史
