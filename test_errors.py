import subprocess
import os
import re

cub_dir = "assets/map/errors"
cub_files = [f for f in os.listdir(cub_dir) if not f.startswith(".")]

EXECUTABLE = "./cub3D"

print("=== Tests d'erreurs cub3D avec Valgrind (toutes erreurs incluses) ===\n")

def valgrind_has_errors(stderr: str) -> bool:
    """Retourne True si Valgrind détecte des erreurs dans son output."""
    match = re.search(r"ERROR SUMMARY:\s*(\d+)\s*errors", stderr)
    return int(match.group(1)) > 0 if match else False

def program_has_error(stdout: str, stderr: str) -> bool:
    """Retourne True si le programme a affiché une erreur dans stdout ou stderr."""
    combined = (stdout + "\n" + stderr).lower()
    return "error" in combined

for file in cub_files:
    path = os.path.join(cub_dir, file)
    try:
        result = subprocess.run(
            ["valgrind", "--leak-check=full", "--show-leak-kinds=all", EXECUTABLE, path],
            capture_output=True,
            text=True,
            timeout=15
        )

        stdout = result.stdout.strip()
        stderr = result.stderr.strip()

        # Segfault
        if result.returncode == -11:
            print(f"\033[91m💥 {file} → SEGFAULT détecté !\033[0m")
            print(f"   ↳ stderr: {stderr}")
            continue

        mem_error = valgrind_has_errors(stderr)
        prog_error = program_has_error(stdout, stderr)

        if prog_error or mem_error:
            print(f"✅ {file} → erreur détectée")
            if stdout:
                print(f"   ↳ stdout:\n{stdout}")
            if mem_error:
                print(f"   ↳ Valgrind output:\n{stderr}")
        else:
            print(f"❌ {file} → aucune erreur détectée alors qu'une erreur était attendue")
            if stdout:
                print(f"   ↳ stdout:\n{stdout}")
            if stderr:
                print(f"   ↳ stderr:\n{stderr}")

    except subprocess.TimeoutExpired:
        print(f"⏱️ {file} → Temps d'exécution dépassé")

    except Exception as e:
        print(f"⚠️ {file} → Erreur lors du test : {e}")

print("\n=== Fin des tests ===")
