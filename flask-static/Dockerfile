FROM python:3.5

RUN groupadd theuser && useradd --create-home --gid theuser --uid 1000 theuser
WORKDIR /home/theuser
ENV HOME /home/theuser
USER theuser


RUN pip install --user flask flask-cors

COPY flask-static.py .
CMD ./flask-static.py


