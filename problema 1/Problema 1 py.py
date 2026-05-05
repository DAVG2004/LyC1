import time

def calcular_con_cronometro(n, x, nombre_archivo):
    inicio_tiempo = time.perf_counter()

   
    coef = [1]
    for i in range(1, n + 1):
        nueva_fila = [1] * (i + 1)
        for j in range(1, i):
            nueva_fila[j] = coef[j-1] + coef[j]
        coef = nueva_fila

    lineas_resultado = []
    lineas_resultado.append(f"--- RESULTADOS PARA (x+1)^{n} ---")
    lineas_resultado.append(f"Valor de x: {x}\n")
    
    terminos = []
    for i in range(n + 1):
        pot = n - i
        if pot == 0: 
            terminos.append(str(coef[i]))
        elif coef[i] == 1: 
            terminos.append(f"x^{pot}")
        else: 
            terminos.append(f"{coef[i]}x^{pot}")
    
    lineas_resultado.append("Polinomio extendido:")
    lineas_resultado.append(" + ".join(terminos) + "\n")

    resultado_f = 0
    lineas_resultado.append("Evaluación paso a paso:")
    for i in range(n + 1):
        exp = n - i
        val_pot = x ** exp
        termino = coef[i] * val_pot
        lineas_resultado.append(f"  Paso {i+1}: {coef[i]} * ({x}^{exp}) = {termino}")
        resultado_f += termino

    fin_tiempo = time.perf_counter()
    tiempo_total = fin_tiempo - inicio_tiempo

    try:
        with open(nombre_archivo, 'w', encoding='utf-8') as f:
            f.write("\n".join(lineas_resultado))
            f.write(f"\n\n{'='*40}")
            f.write(f"\nRESULTADO FINAL f({x}): {resultado_f}")
            f.write(f"\nTIEMPO DE EJECUCIÓN: {tiempo_total:.6f} segundos")
            f.write(f"\n{'='*40}")
        print(f"\nProceso exitoso. Archivo creado: {nombre_archivo}")
    except Exception as e:
        print(f"Error al escribir el archivo: {e}")

if __name__ == '__main__':
    N_OBJETIVO = 100
    ARCHIVO_SALIDA = "resultadoPython.txt"
    
    try:
        entrada_x = float(input(f"Evaluando (x+1)^{N_OBJETIVO}. Ingrese el valor de x: "))
        calcular_con_cronometro(N_OBJETIVO, entrada_x, ARCHIVO_SALIDA)
    except ValueError:
        print("Error: Ingrese un número válido.")