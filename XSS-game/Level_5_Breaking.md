# Level 5 : Breaking

- xss는 단순히 데이터를 escaping하는 만을 의미하진 않는다.
- 때론 DOM에 새로운 엘리먼트 없이도 공격이 가능하다.

![Level%205%20Breaking%20bea4be0e719a452cbc54962e9b464b02/Untitled.png](Level%205%20Breaking%20bea4be0e719a452cbc54962e9b464b02/Untitled.png)

- next=javascript:alert(5); ✅

    ![Level%205%20Breaking%20bea4be0e719a452cbc54962e9b464b02/Untitled%201.png](Level%205%20Breaking%20bea4be0e719a452cbc54962e9b464b02/Untitled%201.png)

    - 용진님 강의에서 들었던 href 속성을 통한 javascript 공격을 시도했다.
    - next를 누르면 href에 들어가있는 주소로 바로 이동하므로 GET방식으로 주소를 바꾸고 공격했더니 a태그가 수정되었고 next를 눌러 성공했다.

    결과 : a태그의 href가 변경되어 스크립트가 실행되었다.

    ![Level%205%20Breaking%20bea4be0e719a452cbc54962e9b464b02/Untitled%202.png](Level%205%20Breaking%20bea4be0e719a452cbc54962e9b464b02/Untitled%202.png)

---