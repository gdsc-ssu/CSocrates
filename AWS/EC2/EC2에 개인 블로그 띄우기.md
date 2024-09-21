### 출처
* [nginx 설정](https://phsun102.tistory.com/45)
* https://thinkj.in
___
### 개요
* [[#들어가며]]
* [[#nginx]]
* [[#nginx의 설정]]
* [[#내 블로그 설정하기]]
* [[#Route53]]
* [[#SEO를 통해 내 사이트 노출하기]]
___
### 들어가며

개인 블로그를 생성하고 싶다는 생각을 계속했다. 티스토리나 velog를 활용할 수도있지만, 정적 웹서버나 DNS등의 학습한 내용들을 써먹고 싶다는 생각이 제법 들었다.

프론트엔드 작업이 발목을 잡았지만, 간단한 프론트엔드 작업 정도는 관련 툴이 많이 존재했기 때문에 생각보다 쉽게 사이트를 제작하는 것이 가능했다. 이에따라 정적 웹서버를 활용해 개인 블로그를 제작하기로 결심했다.

블로그 배포를 위해 생각한 방법은 S3를 활용한 방법과 ec2와 Nginx를 활용한 배포로 총 2가지였다.

S3를 활용해 배포를 진행할 경우 https가 자동으로 적용 된다는 점과 가격이 저렴하다는 이점이 존재했다. 
하지만 WAS로의 확장이 어려워 이후 댓글 등의 기능을 추가하기 위해서는 웹서버를 활용해야겠다는 생각이 들어 nginx를 활용하기로 했다.
___
### nginx

[[웹서버와 nginx]]를 참조하면 nginx에 대한 내용이 이미 잘 정리돼 있다. 우리는 정적 웹서버 및 https 적용을 위해 nginx를 활용한다. 별도의 WAS서버가 존재하지 않기 때문에 리버스 프록시라고 부르기에는 부족함이 존재한다.
___
### nginx의 설정

nginx는 brew를 활용해 손쉽게 설치가 가능하다. 리눅스 환경의 경우 apt나 yum을 활용하면 된다. ec2에서 설치할 경우 AWS Linux를 기준으로 `sudo yum install -y nginx` 명령어로 설치가 가능하다.

nginx를 실행해보자. `127.0.0.1:8080`으로 접속하면 아래와 같은 페이지가 출력된다. mac에서 nginx 실행을 위해서는 `nginx`라고 입력하면 된다.

![500](https://obs3dian.s3.ap-northeast-2.amazonaws.com/EC2%EC%97%90%20%EA%B0%9C%EC%9D%B8%20%EB%B8%94%EB%A1%9C%EA%B7%B8%20%EB%9D%84%EC%9A%B0%EA%B8%B0%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-08-19%20%EC%98%A4%ED%9B%84%2012.11.04.png)

위와 같은 이미지가 확인되면 정상적으로 동작하고 있는 것이다. 이제 우리는 설정을 변경해 nginx가 전송 받은 요청에 따른 적절한 페이지를 전송하게 만들면 된다. 

설정 파일로 접속해보자. 설정 파일은 mac을 기준으로 `/opt/homebrew/etc/nginx` 에 위치한다. 내용을 확인해보면 다음과 같다.

```txt hl:3,17,35

#user  nobody;
worker_processes  1; #사용할 워커 프로세스의 수 nginx 토픽을 참조하자

#error_log  logs/error.log;
#error_log  logs/error.log  notice;
#error_log  logs/error.log  info;

#pid        logs/nginx.pid;


events {
    worker_connections  1024;
}


http {
    include       mime.types;
    default_type  application/octet-stream;

    #log_format  main  '$remote_addr - $remote_user [$time_local] "$request" '
    #                  '$status $body_bytes_sent "$http_referer" '
    #                  '"$http_user_agent" "$http_x_forwarded_for"';

    #access_log  logs/access.log  main;

    sendfile        on;
    #tcp_nopush     on;

    #keepalive_timeout  0;
    keepalive_timeout  65;

    #gzip  on;

    server {
        listen       8080;
        server_name  localhost;

        #charset koi8-r;

        #access_log  logs/host.access.log  main;

        location / {
            root   html;
            index  index.html index.htm;
        }

        #error_page  404              /404.html;

        # redirect server error pages to the static page /50x.html
        #
        error_page   500 502 503 504  /50x.html;
        location = /50x.html {
            root   html;
        }

        # proxy the PHP scripts to Apache listening on 127.0.0.1:80
        #
        #location ~ \.php$ {
        #    proxy_pass   http://127.0.0.1;
        #}

        # pass the PHP scripts to FastCGI server listening on 127.0.0.1:9000
        #
        #location ~ \.php$ {
        #    root           html;
        #    fastcgi_pass   127.0.0.1:9000;
        #    fastcgi_index  index.php;
        #    fastcgi_param  SCRIPT_FILENAME  /scripts$fastcgi_script_name;
        #    include        fastcgi_params;
        #}

        # deny access to .htaccess files, if Apache's document root
        # concurs with nginx's one
        #
        #location ~ /\.ht {
        #    deny  all;
        #}
    }


    # another virtual host using mix of IP-, name-, and port-based configuration
    #
    #server {
    #    listen       8000;
    #    listen       somename:8080;
    #    server_name  somename  alias  another.alias;

    #    location / {
    #        root   html;
    #        index  index.html index.htm;
    #    }
    #}


    # HTTPS server
    #
    #server {
    #    listen       443 ssl;
    #    server_name  localhost;

    #    ssl_certificate      cert.pem;
    #    ssl_certificate_key  cert.key;

    #    ssl_session_cache    shared:SSL:1m;
    #    ssl_session_timeout  5m;

    #    ssl_ciphers  HIGH:!aNULL:!MD5;
    #    ssl_prefer_server_ciphers  on;

    #    location / {
    #        root   html;
    #        index  index.html index.htm;
    #    }
    #}
    include servers/*;
}

```

nginx의 설정 파일은 http 블록과 http 블록 내부의 sever블록으로 구분된 것을 확인할 수 있다. http 블록은 http 프로토콜 요청에 대한 처리 방식을 담고 있고 server 블록은 http 요청을 처리하는 각각의 서버를 의미한다.

#### http 블록
http 블록에서는 서버 전체에 포괄적으로 적용되는 속성들을 주로 정의한다. 대표적으로 다음과 같은 옵션들이 존재한다.
* **keepalive_timeout**
	지속 커넥션의 유지시간을 결정한다. 해당 시간까지 클라이언트가 명시적으로 연결을 종료하지 않는 이상 연결이 서버에선 계속 유지된다.
* 파일 전송 허락 여부
* 활용 할 MIME 지정
* HTTP 바디 및 헤더 크기 지정
* gzip 사용 여부
#### server 블록
서버 블록에서는 각각의 서버에 적용되는 속성들을 정의한다. URL과 포트 등을 여기서 설정한다. 몇가지 주요한 속성들을 살펴볼 필요가 존재한다.
* **listen**
	서버에서 요청을 수신하는 서버 명을 설정하는 옵션이다. nginx는 해당 호스트 명으로 전달된 요청을 이 서버 블록으로 전달한다.
* **root**
	요청에 따른 응답으로 전달할 정적 파일 폴더의 기본 위치를 설정한다. `servername/a.html` 이라는 요청이 전송되면 루트 디렉토리 하위에 위치한 `a.html`을 반환한다.
* **index**
	index 페이지로 사용할 페이지를 등록한다. 
* **location**
	경로 별로 처리할 요청을 지정하기 위해 사용한다. `/`와 같이 입력하며 해당 경로로 들어온 요청을 설정할 때 사용한다.
* **return**
	사용자에게 특정 응답 코드를 반환하기 위해 활용한다. 응답 코드와 텍스트를 반환한다. 리다이렉팅이나 에러코드 처리를 위해 주로 활용한다.
* **rewrite**
	클라이언트의 요청 URL을 덮어써 다른 경로로 수정할 때 주로 활용한다. 리턴과 달리 반환을 곧장 하지 않고 수정된 URL로 변경후 해당 URL에 적절한 처리를 진행한 후 반환한다.
* **ssl_certificate_key**
	HTTPS 적용을 위한 SSL 키 파일을 적용하기 위해 사용하는 속성이다. 키 파일의 경로를 입력한다.

___
### 내 블로그 설정하기

설정 파일에 어떠한 요소가 있는지 파악했으니 이에 따른 적절한 설정을 진행해보자. 우리가 설정해야 할 것들은 다음과 같다.

#### 사용할 워커 프로세스
nginx는 비동기 방식으로 동작하고 각 워커 프로세스는 이벤트 루프에서 이벤트 드리븐 방식으로 요청을 처리한다. 워커 프로세스는 하나의 커넥션만을 담당하지 않고 이벤트 루프에서 이벤트가 발생한 모든 요청을 처리하므로 하드웨어의 모든 자원을 활용한다. (CPU가 노는 시간이 발생하지 않는다) 따라서 **워크 프로세스의 수는 일반적으로 CPU 코어 수로 결정한다.**

>[!info]
> **모든 워커는 비동기 방식으로 동작하고 이러한 까닭에 워커의 수를 무작정 늘린다고 해서 웹서버의 성능이 향상 되지는 않는다.** 

우리가 사용할 ec2는 가장 저렴한 t2 micro이기 때문에 워커 프로세스의 수를 1개로 설정한다. 

#### 요청 별 반환 파일 지정
이제 요청에 따라 전달할 파일의 위치를 지정해보자. 우리는 사용자가 요청을 경로 단위로 아름답게 전송할 것이라 가정하기 때문에 (`thinkj.in/aws/s3.html` 이러한 방식으로) 루트만 잘 설정해주고 사용자의 요청에 따른 적절한 파일만 반환 해준다.

```
root /home/ec2-user/my_blog;
location / {
		if (-d $request_filename) {
				rewrite ^(.*)$ /readme.html redirect;
		 } #만약 요청이 디렉토리 명이면 인덱스로 리다이렉팅
		index readme.html;
		autoindex off; #자동 생성 인덱스 페이지를 비활성화한다.
}
```

이렇게 설정해두면 모든 요청은 해당 로케이션으로 전달된다. 이때 루트는 `/home/ec2-user/my_blog` 이므로 `https://thinkj.in/aws/s3.html`과 같은 요청이 전달되면 `/home/ec2-user/my_blog/aws/s3.html`을 반환한다.

#### HTTPS
현재 사이트에 접속하려고 하면 사이트가 안전하지 않다는 문구와 함께 접속이 제한될 것이다. 이는 HTTPS를 제공하지 않기 때문으로 해결을 위해서는 인증서를 발급받고 SSL 프로토콜을 지원해야한다.
CA 인증서는 일반적으론 유료 지만 [let's encrypt](https://letsencrypt.org/certificates/) 등을 활용하면 쉽게 무료 인증서를 발급 받을 수 있다. 

발급받은 인증서와 키를 nginx 설정에 입력하면 HTTPS 접속을 제공할 수 있다.

```txt hl:4,5
server {
        listen       443 ssl http2;
        server_name  thnikj.in www.thinkj.in;
        ssl_certificate /etc/letsencrypt/live/thinkj.in/fullchain.pem;
        ssl_certificate_key /etc/letsencrypt/live/thinkj.in/privkey.pem;
        root /home/ec2-user/my_blog;
        charset utf-8;

        # Load configuration files for the default server block.
        include /etc/nginx/default.d/*.conf;
        index readme.html;

        location / {
                if (-d $request_filename) {
                        rewrite ^(.*)$ /readme.html redirect;
                 }
                index readme.html;
                autoindex off;
        }
```

443 포트만 제공할 경우 80번 포트로 접속하면 접속이 아예 불가하므로 만약 80번 포트로 접속할 경우 443으로 리다이렉팅을 진행해 HTTPS로 접속을 진행하게 하자. 앞에서 배운 return을 활용해 리다이렉팅을 진행한다.

```text hl:4
  server {
        listen 80;
        server_name thinkj.in www.thinkj.in;
        return 301 https://$host$request_uri; #host와 request는 그대로 https만 적용해 리다이렉트한다.
    }
```

> [!info]
> **이제 원하는 정적 파일을 요청에 따라 반환하고 이를 HTTPS 위에서 진행하는 것이 가능해졌다.**

___
### Route53

블로그를 다 만들었다고 해도 과언이 아니지만, 아직까지 ip 주소를 기반으로 접속을 진행해야 한다는 불편이 존재한다. 이를 해결하기 위해 적절한 도메인을 구매하고 이를 DNS 레코드에 추가하는 작업을 수행해보자.

우선적으로 가비아나 Route53에서 제공하는 도메인을 구매하자. 결제는 어렵지 않으니 생략한다. 결제를 진행하고나면 해당 도메인을 route53등의 DNS 서비스에 등록하면 된다. 

호스팅 영역을 추가하자.

![](https://obs3dian.s3.ap-northeast-2.amazonaws.com/EC2%EC%97%90%20%EA%B0%9C%EC%9D%B8%20%EB%B8%94%EB%A1%9C%EA%B7%B8%20%EB%9D%84%EC%9A%B0%EA%B8%B0%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-08-19%20%EC%98%A4%ED%9B%84%203.52.20.png)

영역을 추가하고 나면 레코드를 추가하면 된다. 내가 보유하고 있는 도메인 명을 입력하고 이와 매핑할 EC2의 퍼블릭 ip를 넣어준다. 이제 접속을 진행해보자.

![300](https://obs3dian.s3.ap-northeast-2.amazonaws.com/EC2%EC%97%90%20%EA%B0%9C%EC%9D%B8%20%EB%B8%94%EB%A1%9C%EA%B7%B8%20%EB%9D%84%EC%9A%B0%EA%B8%B0%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-08-19%20%EC%98%A4%ED%9B%84%203.54.43.png)

[링크](https://thinkj.in/readme.html)를 눌러보면 도메인을 통해 정상적으로 접속이 진행되는 것을 확인해볼 수 있다.
___
### SEO를 통해 내 사이트 노출하기

사이트를 배포했다면 이제 검색엔진 등을 통해 사람들이 접속 가능하게 해야한다. 내 사이트를 검색엔진에 노출 시키기 위해선 다음과 같은 작업을 진행해야 한다. 우선 구글 [웹 마스터](https://search.google.com/search-console?hl=ko&resource_id=sc-domain:thinkj.in)도구로 이동한다.

특정 사이트에 대한 웹 마스터 권한을 확보하기 위해서는 도메인에 TXT 레코드를 추가해 구글에서 명시한 별도의 값을 입력해주면 된다. (복잡하지 않다)

이제 색인을 생성해보자. 구글이 내 사이트를 찾게 하기 위해선 색인을 등록해주면 된다. 색인 등록을 위해선 웹 마스터 도구에서 상단에 위치한 상단 바 메뉴를 활용하면 된다.

![500](https://obs3dian.s3.ap-northeast-2.amazonaws.com/EC2%EC%97%90%20%EA%B0%9C%EC%9D%B8%20%EB%B8%94%EB%A1%9C%EA%B7%B8%20%EB%9D%84%EC%9A%B0%EA%B8%B0%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-08-19%20%EC%98%A4%ED%9B%84%204.03.53.png)

내가 색인 생성을 원하는 URL을 검색한 후 구글에 색인을 생성해 달라 요청하면 구글이 색인을 생성 해준다.
문제는 이러한 작업을 사이트에 존재하는 모든 페이지에 대해 진행할 수는 없다는 것이다. 이에 따라 **구글 크롤러가 자동으로 페이지를 수집할 수 있게 해야하는데 이를 위해선 사이트 맵을 작성할 필요가 있다.**

>[! 사이트 맵이란?]
>**사이트 맵은 크롤러가 사이트의 구조를 파악 가능하게해 더 명확한 크롤링을 가능하게 해준다.**

```xml
<urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.sitemaps.org/schemas/sitemap/0.9 http://www.sitemaps.org/schemas/sitemap/0.9/sitemap.xsd">
<!--  created with Free Online Sitemap Generator www.xml-sitemaps.com  -->
<url>
<loc>https://thinkj.in/readme.html</loc>
<lastmod>2024-07-11T07:26:23+00:00</lastmod>
</url>
</urlset>
```