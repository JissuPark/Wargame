# Level 2 : Persistence is key

- 웹 앱은 사용자의 데이터를 서버나 크라이인트 DB에 저장하고 나중에 사용자에게 보여준다.
- 언제든 user-controlled data는 주의해서 다뤄야한다.
- 내가 만든 데이터에 코드를 숨기면 저장했다가 언제든 보여줄 것이다.

![Level%202%20Persistence%20is%20key%20a5d32be7a0d3496abf7d4724ecea9050/Untitled.png](Level%202%20Persistence%20is%20key%20a5d32be7a0d3496abf7d4724ecea9050/Untitled.png)

- alert(1); ❌

    ![Level%202%20Persistence%20is%20key%20a5d32be7a0d3496abf7d4724ecea9050/Untitled%201.png](Level%202%20Persistence%20is%20key%20a5d32be7a0d3496abf7d4724ecea9050/Untitled%201.png)

    ![Level%202%20Persistence%20is%20key%20a5d32be7a0d3496abf7d4724ecea9050/Untitled%202.png](Level%202%20Persistence%20is%20key%20a5d32be7a0d3496abf7d4724ecea9050/Untitled%202.png)

    결과 : blockquote 태그 안에 문자열이 그대로 들어가는 것을 볼 수 있다. 

    ⇒ 이전 문제처럼 script 태그를 넣어본다.

- <script>alert(1);</script> ❌

    ![Level%202%20Persistence%20is%20key%20a5d32be7a0d3496abf7d4724ecea9050/Untitled%203.png](Level%202%20Persistence%20is%20key%20a5d32be7a0d3496abf7d4724ecea9050/Untitled%203.png)

    ![Level%202%20Persistence%20is%20key%20a5d32be7a0d3496abf7d4724ecea9050/Untitled%204.png](Level%202%20Persistence%20is%20key%20a5d32be7a0d3496abf7d4724ecea9050/Untitled%204.png)

    결과 : script 태그는 인식되었지만 동작하지 않는다. 

    ⇒ 왜 인식만 되고 동작하지 않는지 알 수 없다. 

    ⇒ 용진님 강의를 듣다가 stored xss가 생각나서 저장되고 불러와서 실행되는 부분이 stored xss로 접근하면 될 것 같다는 생각이 들었다.

- <img src=213 onerror=alert(2);> ✅

    ![Level%202%20Persistence%20is%20key%20a5d32be7a0d3496abf7d4724ecea9050/Untitled%205.png](Level%202%20Persistence%20is%20key%20a5d32be7a0d3496abf7d4724ecea9050/Untitled%205.png)

    결과 : 이미지를 클릭하면 이미지 태그의 src를 참조할 수 없기 때문에 onerror의 alert가 실행된다.

    ![Level%202%20Persistence%20is%20key%20a5d32be7a0d3496abf7d4724ecea9050/Untitled%206.png](Level%202%20Persistence%20is%20key%20a5d32be7a0d3496abf7d4724ecea9050/Untitled%206.png)

---