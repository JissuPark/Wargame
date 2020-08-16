# LOS - cobolt

```php
<?php
  include "./config.php"; 
  login_chk();
  $db = dbconnect();
  if(preg_match('/prob|_|\.|\(\)/i', $_GET[id])) exit("No Hack ~_~"); 
  if(preg_match('/prob|_|\.|\(\)/i', $_GET[pw])) exit("No Hack ~_~"); 
  $query = "select id from prob_cobolt where id='{$_GET[id]}' and pw=md5('{$_GET[pw]}')"; 
  echo "<hr>query : <strong>{$query}</strong><hr><br>"; 
  $result = @mysqli_fetch_array(mysqli_query($db,$query)); 
  if($result['id'] == 'admin') solve("cobolt");
  elseif($result['id']) echo "<h2>Hello {$result['id']}<br>You are not admin :(</h2>"; 
  highlight_file(__FILE__); 
?>
```

query에 대해서 알고 있다면 쉽게 풀 수 있는 문제이다. 
다행이도 이 문제에서는 query가 보내지는 것을 보여주는 echo구문이 있어서 풀기에 어려움이 덜했다. 

처음에는 pw부분의 md5에 주목해서 아래와 같이 md5부분을 닫아주는 식으로 답을 찾아 갔지만 그렇게 접근하니 pw뿐만 아니라 id부분까지 검사하지 않게되어 if($result['id'])구문에서 else로 가버리는 문제가 발생했다. 

```sql
query : select id from prob_cobolt where id='admin' and pw=md5('') or ('1=1')
```

그래서 id부분에 초점을 맞추고 id가 admin인 상태에서 pw를 검사하지 않는 것을 시도해 보았다. 여러가지 시도 끝에 아래와 같은 구문으로 답을 찾았다. (주석을 처리하는 부분은 #, /*, --을 모두 시도해보았지만 --만 답을 내주었다.)

![1565198030144](C:\Users\qkrwl\Documents\web\los\LOS - cobolt-clear.png)