# Level 1 : Hello, world of XSS

- 적절한 escaping없이 사용자의 입력을 받아들인다.
- GET방식을 사용하므로 URL을 통해서도 공격이 가능하다.
- alert()로 pop up창을 띄운다.

![https://raw.githubusercontent.com/JissuPark/Wargame/master/XSS-game/Level_1_Hello%2C_world_of_XSS/Untitled%201.png]()

- alert(1); ❌

    ![Level%201%20Hello,%20world%20of%20XSS%209f0712233cbe4beaaa304e0ac23edfb8/Untitled%201.png](Level%201%20Hello,%20world%20of%20XSS%209f0712233cbe4beaaa304e0ac23edfb8/Untitled%201.png)

    결과 : 쿼리가 b태그에 담기는 것을 확인 할 수 있다. 

    ⇒ script 태그를 통해 시도해본다.

- <script>alert(1);</script> ✅

    ![Level%201%20Hello,%20world%20of%20XSS%209f0712233cbe4beaaa304e0ac23edfb8/Untitled%202.png](Level%201%20Hello,%20world%20of%20XSS%209f0712233cbe4beaaa304e0ac23edfb8/Untitled%202.png)

    결과 : 스크립트 태그를 확인하지 않아서 b태그안에 script태그가 들어가면서 실행된다.

    ![Level%201%20Hello,%20world%20of%20XSS%209f0712233cbe4beaaa304e0ac23edfb8/Untitled%203.png](Level%201%20Hello,%20world%20of%20XSS%209f0712233cbe4beaaa304e0ac23edfb8/Untitled%203.png)

---
