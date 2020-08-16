# LOS - vampire

```php
<?php 
  include "./config.php"; 
  login_chk(); 
  $db = dbconnect(); 
  if(preg_match('/\'/i', $_GET[id])) exit("No Hack ~_~");
  $_GET[id] = strtolower($_GET[id]);
  $_GET[id] = str_replace("admin","",$_GET[id]); 
  $query = "select id from prob_vampire where id='{$_GET[id]}'"; 
  echo "<hr>query : <strong>{$query}</strong><hr><br>"; 
  $result = @mysqli_fetch_array(mysqli_query($db,$query)); 
  if($result['id'] == 'admin') solve("vampire"); 
  highlight_file(__FILE__); 
?>
```

이 문제는 전 문제에서 우회할 수 있었던 대소문자 구분을 없애기 위해서 받은 문자열을 모두 lower casting하는 부분이 추가되고 admin이라는 글자가 들어오면 제거해주기까지 한다. 

여기서 취약한 부분을 생각할 수 있다면 아주 쉬운 문제가 되는데, 
admin이라는 글자만 삭제해준다면 'aadmindmin'과 같이 admin사이에 admin이 들어간다면 중간에 있는 admin이 삭제되고 query에는 admin이라는 글자만 남아서 문제가 풀리게된다. 

```url
https://los.rubiya.kr/chall/vampire_e3f1ef853da067db37f342f3a1881156.php?id=aadmindmin
```

![1565331427130](C:\Users\qkrwl\Documents\web\los\LOS - vampire-clear)