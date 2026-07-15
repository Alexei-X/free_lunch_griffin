import secrets

def legendre_symbol(a, p):
    a %= p
    if a == 0:
        return 0

    ls = pow(a, (p - 1) // 2, p)
    return -1 if ls == p - 1 else ls

def random_nonresidue(p):
    while True:
        x = secrets.randbelow(p - 1) + 1
        if legendre_symbol(x, p) == -1:
            return x

def generate_pairs(p, count=3):
    inv4 = pow(4, -1, p)

    deltas = []
    mus = []

    for _ in range(count):
        delta = secrets.randbelow(p)
        n = random_nonresidue(p)

        mu = ((delta * delta - n) * inv4) % p

        # Verify
        disc = (delta * delta - 4 * mu) % p
        assert legendre_symbol(disc, p) == -1

        deltas.append(delta)
        mus.append(mu)

    return deltas, mus

if __name__ == "__main__":
    p = 922337203687

    deltas, mus = generate_pairs(p)

    print("deltas =", deltas)
    print("mus    =", mus)

    for i in range(3):
        disc = (deltas[i] * deltas[i] - 4 * mus[i]) % p
        print(f"disc_{i} = {disc}")
