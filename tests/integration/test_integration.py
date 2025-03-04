import subprocess

APP_PATH = "./build/app.exe"

def run_calc(input_str, args=[]):
    """Запускает калькулятор с входной строкой и возвращает результат."""
    res = subprocess.run([APP_PATH] + args, input=input_str, text=True, capture_output=True)
    return res

def test_sum_int():
    res = run_calc("2+2")
    assert res.returncode == 0
    assert res.stdout.strip() == "=4"

def test_mult_int():
    res = run_calc("12*5")
    assert res.returncode == 0
    assert res.stdout.strip() == "=60"

def test_many_expressions_int():
    res = run_calc("2+2*2+(6/2)")
    assert res.returncode == 0
    assert res.stdout.strip() == "=9"

def test_many_expressions_float():
    res = run_calc("4*5/(8+13)", ["--float"])
    assert res.returncode == 0
    assert res.stdout.strip() == "=0.9524"

def test_wrong_symbol():
    res = run_calc("4*x")
    assert res.returncode != 0

def test_lot_space():
    res = run_calc("4          *2")
    assert res.returncode == 0
    assert res.stdout.strip() == "=8"

def test_lot_braces():
    res = run_calc("(((2+3)")
    assert res.returncode != 0

def test_division_by_zero():
    res = run_calc("10/0")
    assert res.returncode != 0

def test_lot_symbols_in_expression():
    res = run_calc("3++++3")
    assert res.returncode != 0

def test_max_number():
    res = run_calc("2000000001+1")
    assert res.returncode != 0

def test_un_minus():
    res = run_calc("-2+1")
    assert res.returncode != 0
