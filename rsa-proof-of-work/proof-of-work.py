import hashlib
import random
import string

def convert_to_sha256(bs):
    return hashlib.sha256(bs).hexdigest()

def generate_8_byte():
    e = ''.join(random.choice(string.ascii_uppercase + string.ascii_lowercase + string.digits) for _ in range(8))
    return e, str.encode(e)

def main():
    while 1:
        plain, as_bytes = generate_8_byte()
        hs = convert_to_sha256(as_bytes)
        if (hs[0:3] == "000"):
            print(plain, " : ", hs)
            return 

if __name__ == "__main__":
    main()
