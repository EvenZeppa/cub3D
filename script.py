import os
import re
import sys
from collections import defaultdict

def extract_function_calls(file_path, call_counter):
    # Regex pour détecter les appels de fonctions
    function_call_pattern = re.compile(r'\b([a-zA-Z_]\w*)\s*\(')

    # Mots-clés à ignorer (structures du langage)
    excluded_keywords = {
        'if', 'while', 'for', 'switch', 'return', 'sizeof',
        'else', 'do', 'case', 'break', 'continue'
    }

    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
        lines = f.readlines()

    for lineno, line in enumerate(lines, start=1):
        matches = function_call_pattern.findall(line)
        for match in matches:
            if match not in excluded_keywords:
                print(f"{file_path}:{lineno} -> {match}")
                call_counter[match] += 1

def scan_directory_for_functions(directory):
    call_counter = defaultdict(int)
    for root, _, files in os.walk(directory):
        for filename in files:
            if filename.endswith('.c'):
                file_path = os.path.join(root, filename)
                extract_function_calls(file_path, call_counter)

    print("\n📊 RÉCAPITULATIF DES FONCTIONS UTILISÉES :")
    for func, count in sorted(call_counter.items(), key=lambda x: (-x[1], x[0])):
        print(f"{func}: {count} fois")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python scan_functions.py <chemin_du_dossier>")
    else:
        scan_directory_for_functions(sys.argv[1])
