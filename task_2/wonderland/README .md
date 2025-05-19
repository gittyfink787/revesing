
# פענוח וונדרלנד – שלב 2

## שלבי העבודה:

- פתחנו את הקובץ הראשי. נכנסנו לתפריט ומשם לקוד האחראי על הפונקציונליות של שלב 2.
- בסקירה כללית של תרשים הזרימה של הקוד אנו מסיקים מכיווני החיצים ומצורת החלוקה שמדובר בלולאה מקוננת.
- ![image](https://github.com/user-attachments/assets/f6d5c32d-dc1f-4e42-880b-a390f3f5002e)


## כניסה לקוד:

- הקוד יוצר 2 משתנים לוקאליים ו־BUFFER בגודל 1024 בתים. סך כל ההקצאות: 1036 בתים.
- ![image](https://github.com/user-attachments/assets/1a1a4c68-577a-4a07-9027-dd3ab0960433)

- לפני הלולאה – הקוד מדפיס מחרוזת.
- ![image](https://github.com/user-attachments/assets/323be109-961f-42f0-8027-0b7e1dfe05ff)

- בכניסה ללולאה – קיימת קפיצה בלתי מותנית לתוך הלולאה.
- ![image](https://github.com/user-attachments/assets/9c506635-eec8-44f9-a0ad-a9827ec00091)


## גוף הלולאה:

- תחילת הלולאה: קריאה ל־`memset` שמאתחלת את כל ה־BUFFER לאפסים (פונקציה מיובאת).
- במעבר לקוד של הפונקציה אנו מגיעים לשורות הבאות:
-![image](https://github.com/user-attachments/assets/4cf720d2-0194-47c8-8d5a-0019f98efbc1)
אנו מבינים מהתוכן שהפונקציה מיובאת.
- חיפוש באינטרנט מניב:![image](https://github.com/user-attachments/assets/434a6610-87e1-497a-9131-d04eab758486)

- לאחר מכן: 2 קריאות לפונקציות מערכת שמכניסות קלט מהמשתמש אל תוך ה־BUFFER.
- קריאה ל־`strlen` – מחזירה את אורך הקלט ונשמרת במשתנה `len`.

## משתנים:

- משתנה בשם `VAR_4` מאותחל לאפס – זוהה כאינדקס ולכן שמו שונה ל־`i`.
- טיפוס המערך שונה מ־CHAR ל־INT_32 בעקבות השימוש ב־XOR על תאים ב־BUFFER.

## הלולאות:

- הלולאה הפנימית היא לולאת `for` קלאסית – מבצעת `XOR` על איברי `buffer[i]`.
- הלולאה החיצונית – לולאת `do-while`, משווה בין הקלט למחרוזת `"into the rabbit hole"` שבוצע עליה XOR עם מפתח הנתון בקוד.
  - אם יש התאמה – יציאה מהלולאה.
  - אם לא – ממשיכים בלולאה.
  ## פיצוח הסיסמא:
  יצרנו קוד פייתון שהפעיל XOR על המחרוזת "into the rabbit hole" עם המפתח המתאים מהקוד.
```python
def xor_string_with_key(s, key=0x41524241):
    s_bytes = bytearray(s, 'ascii')
    output = bytearray(len(s_bytes))

    # XOR בקבוצות של 4 תווים
    for i in range(0, len(s_bytes) - (len(s_bytes) % 4), 4):
        block = int.from_bytes(s_bytes[i:i+4], 'little')
        xor_block = block ^ key
        output[i:i+4] = xor_block.to_bytes(4, 'little')

    # שארית (אם אורך המחרוזת אינו כפולה של 4)
    for i in range(len(s_bytes) - (len(s_bytes) % 4), len(s_bytes)):
        output[i] = s_bytes[i] ^ (key & 0xFF)

    # החזר מחרוזת
    return output.decode('ascii')
```
#  דוגמה לשימוש:
original = "into the rabbit hole"
encrypted = xor_string_with_key(original)
decrypted = xor_string_with_key(encrypted)

print(" מוצפן:", encrypted)
print(" מפוענח:", decrypted)
## הרצה מוצלחת:
- הזנו את תוצאת סקריפט הפייתון כקלט לתוכנית, וקיבלנו הודעת הצלחה:
![image](https://github.com/user-attachments/assets/09ac68de-9c05-441d-9690-aefe68b71f2c)

## סוף התהליך:

- מודפסת הודעת הצלחה עם היציאה מהלולאה.
- ההרצה נכשלה במקור בגלל שה־BUFFER הוגדר כ־INT_32 במקום CHAR.
- שינוי סוג המערך ל־CHAR פתר את הבעיה.
- קוד פייתון שימש להצפנת `"into the rabbit hole"` לפי הקבוע שבקוד.
- התוצאה הרצויה הוזנה בטרמינל ונמצאה תקינה.
