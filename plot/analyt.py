import json
import numpy as np
from scipy.stats import norm


def option_value():

    with open('input.json') as input_data:
        data = json.load(input_data)
    
        option_type = data["european option"]["type"]
        interest_rate = data["european option"]["interest rate"]
        volatility = data["european option"]["volatility"]
        strike_price = data["european option"]["strike price"]
        dividend = data["european option"]["dividend"]

        S_min = data["domain"]["underlying"]["minimum"]
        S_max = data["domain"]["underlying"]["maximum"]
        S_steps = data["domain"]["underlying"]["steps"]
        #print(data["domain"])

        S = np.linspace(S_min, S_max, S_steps)
        time = data["domain"]["time"]["maximum"] - data["domain"]["time"]["minimum"]

        # print(S)
        d1 = ( np.log(S / strike_price) + 
                 (interest_rate - dividend + volatility * volatility / 2) * time) / \
                      (volatility * np.sqrt(time))
        d2 = d1 - volatility * np.sqrt(time)

        if option_type == 'call':
            C = norm.cdf(d1) * S * np.exp(-dividend * time) - \
                  norm.cdf(d2) * strike_price * np.exp(-interest_rate * time)
            delta = norm.cdf(d1)
        else:  # put
            C = norm.cdf(-d2) * strike_price * np.exp(-interest_rate * time) - \
                  norm.cdf(-d1) * S * np.exp(-dividend * time) 
            delta = norm.cdf(d1) - 1

        gamma = norm.pdf(d1) / (S * volatility * np.sqrt(time))


        return S, C, delta, gamma
