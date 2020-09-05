# Level 2 : Persistence is key

- 웹 앱은 사용자의 데이터를 서버나 크라이인트 DB에 저장하고 나중에 사용자에게 보여준다.
- 언제든 user-controlled data는 주의해서 다뤄야한다.
- 내가 만든 데이터에 코드를 숨기면 저장했다가 언제든 보여줄 것이다.

![](https://github.com/JissuPark/Wargame/blob/master/XSS-game/Level_2_Persistence_is_key/Untitled.png?raw=true)

- alert(1); ❌

    ![](https://github.com/JissuPark/Wargame/blob/master/XSS-game/Level_2_Persistence_is_key/Untitled%201.png?raw=true)

    ![](https://github.com/JissuPark/Wargame/blob/master/XSS-game/Level_2_Persistence_is_key/Untitled%202.png?raw=true)
)

    결과 : blockquote 태그 안에 문자열이 그대로 들어가는 것을 볼 수 있다. 

    ⇒ 이전 문제처럼 script 태그를 넣어본다.

- <script>alert(1);</script> ❌

  ![](https://github.com/JissuPark/Wargame/blob/master/XSS-game/Level_2_Persistence_is_key/Untitled%203.png?raw=true)

    ![](https://github.com/JissuPark/Wargame/blob/master/XSS-game/Level_2_Persistence_is_key/Untitled%204.png?raw=true)
  

    결과 : script 태그는 인식되었지만 동작하지 않는다. 

    ⇒ 왜 인식만 되고 동작하지 않는지 알 수 없다. 

    ⇒ 용진님 강의를 듣다가 stored xss가 생각나서 저장되고 불러와서 실행되는 부분이 stored xss로 접근하면 될 것 같다는 생각이 들었다.

- <img src=213 onerror=alert(2);> ✅

    ![](https://github.com/JissuPark/Wargame/blob/master/XSS-game/Level_2_Persistence_is_key/Untitled%205.png?raw=true)

    결과 : 이미지를 클릭하면 이미지 태그의 src를 참조할 수 없기 때문에 onerror의 alert가 실행된다.

    ![](https://github.com/JissuPark/Wargame/blob/master/XSS-game/Level_2_Persistence_is_key/Untitled%206.png?raw=true)

---
