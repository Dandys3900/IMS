# IMS-Projekt

## Formát JSON konfiguračního souboru
Pro zajištění korektního běhu simulačního programu je nezbytné dodržet následující pravidla.

Pořadí definování jednotlivých entit/účastníků dle typu je pevně dáno následovně:

1. "type" : "sim_duration" [! Očekávaná pouze jedna entita tohoto typu !]
2. "type" : "coin"
3. "type" : "investor_*"
4. "type" : "exchange"
5. "type" : "government" [! Očekávaná pouze jedna entita tohoto typu !]
6. "type" : "miner"
7. "type" : "elon_tweeter"
8. "type" : "tech_dev"

Přičemž atributy entity každého typu jsou rovněž dané, jak lze vidět níže:
1. `"sim_duration"`
    - `"sim_duration_years" : [unsigned int]`
2. `"coin"`
    - `"name" : [unique string]`
    - `"initial_price" : [double/int > 0]`
    - `"mining_efficiency" : [0.0 - 1.0]`
    - `"total_supply" : [unsigned int]`
    - `"circulating_supply" : [unsigned int]`
3. `"investor_*"`
    - `"coins" : [`
        - `{`
            - `[název vytvořené mince] : [unsigned int] (výchozí vlastněný počet)`
            - `"sell_threshold" : [double/int > 0] (pokud hodnota mince přesáhne tuto hodnotu, zahájí prodej)`
            - `"buy_threshold" : [double/int > 0] (pokud hodnota mince klesne pod tuto hodnotu, zahájí nákup)`
        - `}`
        - `...`
    - `]`
4. `"exchange"`
    - `"fee" : [0.0 - 1.0]`
    - `"initial_coin_amount" : {`
        - `[název vytvořené mince] : [unsigned int] (výchozí vlastněný počet)`
        - `... (výčet pro další mince)`
    - `}`
5. `"government"`
    - `"init_taxes" : [0.0 - 1.0]`
6. `"miner"`
    - `"intial_mining_rate_per_hour" : [unsigned int]`
    - `"hardware_performance" : [0.0 - 1.0]`
    - `"coins" : [`
        - `[název vytvořené mince]`
        - `... (výčet pro další mince)`
    - `]`
    - `"mining_strategy" : ["random_choice" / "best_choice"] (určuje způsob, jakým si těžař vybere minci, kterou bude pro daný půlden těžit)`
7. `"elon_tweeter"` (nemá žadné atributy)
8. `"tech_dev"`
    - `"mining_performance_boost" : [double/int > 0]`
