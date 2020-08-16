# LOS - troll

```php
<?php  
  include "./config.php"; 
  login_chk(); 
  $db = dbconnect(); 
  if(preg_match('/\'/i', $_GET[id])) exit("No Hack ~_~");
  if(preg_match("/admin/", $_GET[id])) exit("HeHe");
  $query = "select id from prob_troll where id='{$_GET[id]}'";
  echo "<hr>query : <strong>{$query}</strong><hr><br>";
  $result = @mysqli_fetch_array(mysqli_query($db,$query));
  if($result['id'] == 'admin') solve("troll");
  highlight_file(__FILE__);
?>
```

이번 문제는 그동안 보고 있지 않았던 부분을 볼 수 있게 해주는 문제였다. 

지금까지는 소스코드에 나와있던 부분에서 무슨 문자를 필터링하는지만 보았는데 이번 문제를 통해서 preg_match함수에 대해서 알게되었다. 

처음에는 single quote를 어떻게 우회할까에 대한 방법만 고민하다가 \&apos; 같은 문자도 넣어 봤는데 그 뒤에 입력이 들어가지 않았다. 그래서 열심히 찾아보던 중 grep_match함수를 보게되었고 문자열을 찾아내는 방식에 대해서 알게되었다. 

```php
preg_match ( string $pattern , string $subject [, array &$matches [, int $flags = 0 [, int $offset = 0 ]]] ) : int
```

preg_match함수는 pattern에 어떤 옵션을 주느냐에 따라서 다양하게 활용이 가능한데, /b 옵션을 주면 주어진 문자와 완전히 같을 경우만 인정하고 /i 옵션을 주면 대소문자의 구분 없이 인정해서 결과를 반환한다. 더 많은 옵션이 있지만 이 문제에서 중요한 옵션은 i옵션이므로 넘어가도록 한다. 

위에서 설명했듯이 /i 옵션을 주면 대소문자의 구분이 사라지지만 'admin'을 확인하는 구간에서는 /i 옵션을 주지 않았음으로 한 글자라도 대문자가 들어간다면 우회할 수 있게 된다. 그럼 여기서 의문이 하나생기는데 대문자가 들어간 'aDmin'같은 글자로 어떻게 query가 제대로 실행되어 결과를 반환하는 가? 이다. 

이에 대한 대답은 sql에 있다. sql에서는 varchar나 text로 된 값을 대소문자를 구분하지 않고 검색하기때문에 올바른 결과값을 반환해준다.

![1565329024852](C:\Users\qkrwl\Documents\web\los\LOS - troll-clear)