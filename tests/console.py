"""Smoke tests for redirected input, validation and normal console actions."""
import subprocess
import sys

for binary in sys.argv[1:]:
    data = '\n'.join([
        'bad', '1', '99999999999999999999999999999', '1', '-5 -5 0',
        '3', '-5', '2', '-5 123', '3', '-5', '4', '3', '-5', '5', '0', ''
    ])
    result = subprocess.run([binary], input=data, text=True, encoding="utf-8", capture_output=True, timeout=10)
    assert result.returncode == 0, result.stderr
    for expected in ['Choose an option from 0 to 5.', 'Invalid input.', 'Added: 3',
                     'Removed: 1', '-5 — found.', '-5 — not found.',
                     'Loaded 13', 'Nodes: 13', '├──', '└──']:
        assert expected in result.stdout, (binary, expected)
    assert '\x1b' not in result.stdout, 'Redirected output must not contain terminal escapes'
    eof = subprocess.run([binary], input='', text=True, encoding="utf-8", capture_output=True, timeout=10)
    assert eof.returncode == 0
    # A malformed batch must not partially modify the tree.
    invalid = subprocess.run([binary], input='1\n5 nope\n0\n', text=True, encoding="utf-8", capture_output=True, timeout=10)
    assert invalid.returncode == 0 and 'Nodes: 1' not in invalid.stdout
print('Console checks passed')
