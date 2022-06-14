from typing import List
import numpy as np
def generate_poisson_process(rate: float, t: int ) -> List[float]:
    S = []
    elapsed_time = 0
    while elapsed_time <= t:
        time_to_next_event = np.random.exponential(1/rate)
        elapsed_time += time_to_next_event
        if elapsed_time > t:
            break
        S.append((elapsed_time, time_to_next_event))
    return S

computer_fail_rate = 5
switch_fail_rate = 3
order_size = 15
simulation_time = 4
iterations = 100000
success_counter = 0
for i in range(iterations):
    print("Iteration:", i)
    fail_rate = switch_fail_rate + computer_fail_rate
    process = generate_poisson_process(fail_rate, simulation_time)
    n_failures = len(process)
    if n_failures < order_size:
        success_counter += 1
print(f'E: {success_counter/iterations}')