import subprocess
import os

cub_dir = "assets/map/valids"  # Dossier des maps valides
cub_files = [f for f in os.listdir(cub_dir) if not f.startswith(".")]

EXECUTABLE = "./cub3D"

print("=== Tests des maps valides cub3D avec Valgrind (hors erreurs liées à MLX) ===\n")

def is_mlx_leak(output: str) -> bool:
    """Retourne True si toutes les fuites sont liées à la MLX."""
    mlx_keywords = ["mlx_", "libmlx", "minilibx"]
    lines = output.lower().splitlines()
    leaks = [line for line in lines if "definitely lost" in line or "indirectly lost" in line]

    if not leaks:  # aucune fuite → OK
        return False

    # vérifier que toutes les fuites viennent de MLX
    for line in leaks:
        if not any(keyword in line for keyword in mlx_keywords):
            return False
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

        # Pour une map valide : succès attendu
        success = (
            error_code == 0 or valgrind_leak_only_mlx
        ) and "error" not in stdout.lower() and "error" not in stderr.lower()

        if success:
            print(f"✅ {file} → exécutée correctement")
        else:
            print(f"❌ {file} → problème détecté (NON ATTENDU)")
            print(f"   ↳ stdout: {stdout.strip()}")
            print(f"   ↳ stderr: {stderr.strip()}")

    except subprocess.TimeoutExpired:
        print(f"⏱️ {file} → Temps d'exécution dépassé")

    except Exception as e:
        print(f"⚠️ {file} → Erreur lors du test : {e}")

print("\n=== Fin des tests ===")
