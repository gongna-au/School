# what 's Werkzeug ?

> [Werkzeug](https://link.juejin.cn/?target=http%3A%2F%2Fwerkzeug.pocoo.org%2Fdocs%2F0.14%2F) 是一个WSGI工具包，也可以作为一个Web框架的底层库。

## WSGI

（Python Web Server Gateway Interface）为Python语言定义的Web服务器和Web应用程序或框架之间的一种简单而通用的接口。

**WSGI 分为两个部分：**

### Server/Gateway: 

即是HTTP Server,

- 负责从客户端(Nginx、apache、IIS）接收请求
- 将 request 转发给 application, 并将 application（可能是个Flask应用） 返回的response 返回给客户端.



![wsgi server 与 wsgi 应用之间的调用关系](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2018/10/2/16633f1397883223~tplv-t2oaga2asx-zoom-in-crop-mark:1304:0:0:0.awebp)

![web sever 与 wsgi server 与 web browser之间的调用流程](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2018/10/2/16633f139886be69~tplv-t2oaga2asx-zoom-in-crop-mark:1304:0:0:0.awebp)

### Application/Framework: 

- 一个python web 应用或 web 框架接收由 server 转发的request
- 处理请求，并将处理结果返回给 server

## Werkzeug

werkzeug 提供了 python web WSGI 开发相关的功能：

- 路由处理：如何根据请求 URL 找到对应的视图函数

- request 和 response 封装: 提供更好的方式处理request和生成response对象

- 自带的 WSGI server: 测试环境运行WSGI应用

  ```
  from werkzeug.wrappers import Request, Response
  def application(environ, start_response):
      request = Request(environ)
      text = 'Hello %s!' % request.args.get('name', 'World')
      response = Response(text, mimetype='text/plain')
      return response(environ, start_response)
  
  ```

  请求数据需要环境对象，Werkzeug允许你以一个轻松的方式访问数据。响应对象是一个 WSGI 应用，提供了更好的方法来创建响应。**Flask框架中使用到Werkzeug的数据结构。**

**使用werkzeug创建一个web 应用：**

```
import os
import redis
import urlparse
from werkzeug.wrappers import Request, Response
from werkzeug.routing import Map, Rule
from werkzeug.exceptions import HTTPException, NotFound
from werkzeug.wsgi import SharedDataMiddleware
from werkzeug.utils import redirect
from jinja2 import Environment, FileSystemLoader

class Shortly(object):
    """ 
    Shortly 是一个实际的 WSGI 应用，通过 __call__ 方法直接调 用 wsgi_app，
    同时通过一个可选设置创建一个中间件，将static文件夹暴露给用户：
    """
    def __init__(self, config):
        self.redis = redis.Redis(config['redis_host'], config['redis_port'])

    def dispatch_request(self, request):
        return Response('Hello World!')

    def wsgi_app(self, environ, start_response):
        request = Request(environ)
        response = self.dispatch_request(request)
        return response(environ, start_response)

    def __call__(self, environ, start_response):
        return self. wsgi_app(environ, start_response)


def create_app(redis_host='localhost', redis_port=6379, with_static=True):
    app = Shortly({
        'redis_host':       redis_host,
        'redis_port':       redis_port
    })
    if with_static:
        app.wsgi_app = SharedDataMiddleware(app.wsgi_app, {
            '/static':  os.path.join(os.path.dirname(__file__), 'static')
        })
    return app
    
if __name__ == '__main__':
    from werkzeug.serving import run_simple
    app = create_app()
    run_simple('127.0.0.1', 5000, app, use_debugger=True, use_reloader=True)

```

