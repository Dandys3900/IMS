# IMS-Projekt

## Formát JSON konfiguračního souboru
Pro zajištění korektního běhu simulačního programu je nezbytné dodržet formát konfiguračního souboru, jak lze vidět níže:

1. `"simulation_duration_years" : [unsigned int]`
2. `"coins" : [`
    - `{`
      - `"name" : [unique string]`
      - `"initial_price" : [double/int > 0]`
      - `"mining_efficiency" : [0.0 - 1.0]`
      - `"total_supply" : [unsigned int]`
    - `}`
    - `...`
    - `]`
3. `"investors" : [`
    - `{`
      - `"type" : ["long_term" / "short_term"]`
      - `"traded_coins" : [`
        - `{`
          - `"name" : [název vytvořené mince]`
          - `"initial_amount" : [double/int > 0] (výchozí vlastněný počet)`
          - `"sell_threshold" : [double/int > 0] (pokud hodnota mince přesáhne tuto hodnotu, zahájí prodej)`
          - `"buy_threshold" : [double/int > 0] (pokud hodnota mince klesne pod tuto hodnotu, zahájí nákup)`
        - `}`
        - `...`
      - `]`
    - `}`
    - `...`
   - `]`
4. `"exchanges" : [`
    - `{`
      - `"fee" : [0.0 - 1.0]`
      - `"traded_coins" : [`
        - `{`
          - `"name" : [název vytvořené mince]`
          - `"initial_amount" : [double/int > 0]`
        - `}`
        - `...`
      - `]`
    - `}`
    - `...`
    - `]`
5. `"government"`
    - `{`
      - `"init_taxes" : [0.0 - 1.0]`
    - `}`
6. `"miners" : [`
    - `{`
      - `"mining_strategy" : ["random_choice" / "best_choice"] (určuje způsob, jakým si těžař vybere minci, kterou bude pro daný půlden těžit)`
      - `"intial_mining_rate_per_hour" : [unsigned int]`
      - `"hardware_performance" : [0.0 - 1.0]`
      - `"mining_coins" : [`
        - `[název vytvořené mince]`
        - `... (výčet pro další mince)`
      - `]`
    - `}`
    - `...`
    - `]`
7. `"elon_tweeters" : [`
    - `{`
      - `"affected_coin" : [název vytvořené mince]`
    - `}`
    - `...`
    - `]`
8. `"tech_developers" : [`
    - `{`
      - `"mining_performance_boost" : [double/int > 0]`
    - `}`
    - `...`
    - `]`
