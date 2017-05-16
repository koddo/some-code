#!/usr/bin/env python3

## yes, we have `python3 -m http.server 8000`
## but it dropped connections when I had something like hundred js dependencies in index.html (i'm not insane, that's cljs transpiling)
## major inconvenience
## flask does drop them too, but rarely, quite negligible now for dev env
## next step would probably be to use nginx, but not now


from flask import Flask
import logging

app = Flask(__name__, static_url_path='', static_folder='static')


## lets make it not log this:
## 172.17.0.1 - - [19/Dec/2015 18:40:45] "POST /browser_console_logger HTTP/1.1" 204 -
# log = logging.getLogger('werkzeug')   # http://stackoverflow.com/questions/14888799/disable-console-messages-in-flask-server
# log.setLevel(logging.ERROR)


@app.route('/')
def root():
    return app.send_static_file('index.html')

if __name__ == '__main__':
    app.run(host = '0.0.0.0', port = 3448,
            threaded=True)
