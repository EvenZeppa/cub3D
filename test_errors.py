import subprocess
import os

cub_dir = "assets/map/errors"
cub_files = [f for f in os.listdir(cub_dir) if not f.startswith(".")]

EXECUTABLE = "./cub3D"

print("=== Tests d'erreurs cub3D avec Valgrind (hors erreurs liées à MLX) ===\n")

def is_mlx_leak(output: str) -> bool:
    """Retourne True si toutes les fuites sont liées à la MLX."""
    mlx_keywords = ["mlx_", "libmlx", "MiniLibX"]
    lines = output.lower().splitlines()
    leaks = [line for line in lines if "definitely lost" in line or "indirectly lost" in line]

    # Si pas de fuites → c’est bon
    if not leaks:
        return False

    # S’il y a des fuites mais toutes les lignes mentionnent la mlx → ignorer
    for line in leaks:
        if not any(keyword in line for keyword in mlx_keywords):
            return False  # fuite non liée à MLX
    return True

for file in cub_files:
    path = os.path.join(cub_dir, file)
    try:
        result = subprocess.run(
            ["valgrind", "--leak-check=full", "--error-exitcode=123", EXECUTABLE, path],
            capture_output=True,
            text=True,
            timeout=10
        )

        error_code = result.returncode
        stdout = result.stdout
        stderr = result.stderr

        valgrind_failed = error_code == 123
        valgrind_leak_only_mlx = is_mlx_leak(stderr)

        error_detected = (
            error_code != 0 and not valgrind_leak_only_mlx
        ) or "error" in stdout.lower() or "error" in stderr.lower()

        if error_detected:
            print(f"✅ {file} → erreur bien détectée")
        else:
            print(f"❌ {file} → aucune erreur détectée (ATTENDUE)")
            print(f"   ↳ stdout: {stdout.strip()}")
            print(f"   ↳ stderr: {stderr.strip()}")

    except subprocess.TimeoutExpired:
        print(f"⏱️ {file} → Temps d'exécution dépassé")

    except Exception as e:
        print(f"⚠️ {file} → Erreur lors du test : {e}")

print("\n=== Fin des tests ===")
