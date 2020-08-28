# Level 4 : Context Matters

- 유저가 입력한 데이터는 문맥에 맞게 올바르게 필터링 되어야한다.
- 올바르지 않은 입력을 받으면 xss가 트리거되는 이유를 설명한다.

![Level%204%20Context%20Matters%206a6e5b202f2e433dac8834ddac7fa341/Untitled.png](Level%204%20Context%20Matters%206a6e5b202f2e433dac8834ddac7fa341/Untitled.png)

- alert(4); ❌

    ![Level%204%20Context%20Matters%206a6e5b202f2e433dac8834ddac7fa341/Untitled%201.png](Level%204%20Context%20Matters%206a6e5b202f2e433dac8834ddac7fa341/Untitled%201.png)

    결과 : onload속성에 값이 들어가는 것을 확인하고 startTimer함수를 찾기위해 한번 더 실행해서 빠르게 스크립트를 확인할 수 있었다.

    ⇒ 인자로 들어가는 부분이 관건인데 img 태그를 타겟으로 해야하는지, parseInt함수를 타겟으로 해야하는지 고민하다 둘다 해보기로 한다.

    ![Level%204%20Context%20Matters%206a6e5b202f2e433dac8834ddac7fa341/Untitled%202.png](Level%204%20Context%20Matters%206a6e5b202f2e433dac8834ddac7fa341/Untitled%202.png)

    실행되는 동안만 볼 수 있는 startTimer 함수

- img태그를 타겟으로
    - ')alert(4); ❌
    - ')">alert(4); ❌
    - ')"><script>alert(4);</script> ❌

    ⇒ '를 넣었을때 time is up까지 실행되지 않고 계속 도는 것을 확인했다.

- parseInt함수를 타겟으로
    - timer=&#x61;&#x6c;&#x65;&#x72;&#x74;&#x28;&#x31;&#x29;&#59; ❌

⇒ img  태그를 타겟으로 공격하다 보니 ;를 필터링하는 것을 알 수 있었다. 

⇒ 그렇다면 ; 을 쓰지 않고 속성값으로 onerror나 onmouseover를 주어 문법을 맞춰주면 된다.

- '), onmouseover=alert('4 ✅ ❓

    ![Level%204%20Context%20Matters%206a6e5b202f2e433dac8834ddac7fa341/Untitled%203.png](Level%204%20Context%20Matters%206a6e5b202f2e433dac8834ddac7fa341/Untitled%203.png)

    alert은 코드 확인이 안되서 onerror=wait로 바꿔서 캡쳐했다.

    결과 : 인식이 제대로 됐다고 볼 수 있는지 모르겠지만 정상적으로 작동하는 것을 알 수 있었다.

    ⇒ 왜 이렇게 동작하는지에 대한 이유를 더 자세히 알아봐야한다.

    ![Level%204%20Context%20Matters%206a6e5b202f2e433dac8834ddac7fa341/Untitled%204.png](Level%204%20Context%20Matters%206a6e5b202f2e433dac8834ddac7fa341/Untitled%204.png)

- ')", onclick=alert('4 ❌ ❓

    ![Level%204%20Context%20Matters%206a6e5b202f2e433dac8834ddac7fa341/Untitled%205.png](Level%204%20Context%20Matters%206a6e5b202f2e433dac8834ddac7fa341/Untitled%205.png)

    결과 : 문법상으로 보자면 이게 더 맞는 문법인거 같은데 이건 왜 안되는지 이해되지 않았다.

---