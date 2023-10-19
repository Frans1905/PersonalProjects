const data = {
    "website": "Ferton",
    "categories": [
        { 
            "name" : "Gitare",
            "image" : "/images/guitars.jpg",
            "products" : [
                { 
                    "name" : "Fender gitara", "image" : "/images/fender-guitar.jpg"
                },
                { 
                    "name" : "Gibson gitara", "image" : "/images/gibson.jpg"
                },                
                { 
                    "name" : "Ibanez gitara", "image" : "/images/ibanez.jpg"
                },
                {
                    "name" : "Eastman gitara", "image" : "/images/eastman.jpg"
                },
                {
                    "name" : "Yamaha gitara", "image" : "/images/yamaha.jpg"
                }
            ]
        },
        { 
            "name" : "Klavijature",
            "image" : "/images/keys.jpg",
            "products" : [
                { 
                    "name" : "Yamaha electric klavir", "image" : "/images/yamaha-keys.jpg"
                },
                {
                    "name" : "Steinway klavir", "image" : "/images/steinway.jpg"
                },
                {
                    "name" : "Kawai klavir", "image" : "/images/kawai.jpg"
                },
                {
                    "name" : "Schimmel klavir", "image" : "/images/schimmel.jpg"
                },
                {
                    "name" : "Yamaha veliki klavir", "image" : "/images/yamaha-grand.jpg"
                }
            ]
        },
        { 
            "name" : "Pojačala",
            "image" : "/images/amps.jpg",
            "products" : [
                { 
                    "name" : "Fender pojačalo", "image" : "/images/fender-amp.jpg"
                },
                {
                    "name" : "Vox pojačalo", "image" : "/images/vox-amp.jpg"
                },
                {
                    "name" : "Marshall pojačalo", "image" : "/images/marshall-amp.jpg"
                },
                {
                    "name" : "Epiphone pojačalo", "image" : "/images/epiphone-amp.jpg"
                },
                {
                    "name" : "Yamaha pojačalo", "image" : "/images/yamaha-amp.jpg"
                }
            ]
        },
        { 
            "name" : "Zvučnici",
            "image" : "/images/speakers.jpg",
            "products" : [
                { 
                    "name" : "Audiovector zvučnik", "image" : "/images/audiovector-speakers.jpg"
                },
                {
                    "name" : "Portable zvučnik", "image" : "/images/portable-speaker.jpg"
                },
                {
                    "name" : "Soundboks zvučnik", "image" : "/images/soundboks.jpg"
                },
                {
                    "name" : "JBL prijenosni zvučnik", "image" : "/images/jbl.jpg"
                },
                {
                    "name" : "Gibbon zvučnik", "image" : "/images/gibbon.jpg"
                }
            ]
        },
        { 
            "name" : "Bubnjevi",
            "image" : "/images/drums.jpg",
            "products" : [
                { 
                    "name" : "Mapex bubnjevi", "image" : "/images/drums.jpg"
                },
                {
                    "name" : "Djembe bubanj", "image" : "/images/djembe.jpg"
                },
                {
                    "name" : "Set udaraljki", "image" : "/images/set-udaraljke.jpg"
                },
                {
                    "name" : "Bongo bubanj", "image" : "/images/bongo.jpg"
                },
                {
                    "name" : "Elektronički bubnjevi", "image" : "/images/electronic.jpg"
                }
            ]
        },
        { 
            "name" : "Mikrofoni",
            "image" : "speakers.jpg",
            "products" : [
                { 
                    "name" : "Neumann mikrofon", "image" : "/images/neumann.jpg"
                },
                {
                    "name" : "AKG mikrofon", "image" : "/images/AKG.jpg"
                },
                {
                    "name" : "Vintage mikrofon", "image" : "/images/vintage-microphone.jpg"
                },
                {
                    "name" : "Telefunken mikrofon", "image" : "/images/telefunken.jpg"
                },
                {
                    "name" : "Shure mikrofon", "image" : "/images/shure.jpg"
                }
            ]
        },
        { 
            "name" : "Slušalice",
            "image" : "speakers.jpg",
            "products" : [
                { 
                    "name" : "Sony slušalice", "image" : "/images/sony.jpg"
                },
                {
                    "name" : "JBL slušalice", "image" : "/images/jbl-headphones.jpg"
                },
                {
                    "name" : "Airpods", "image" : "/images/airpods.jpg"
                },
                {
                    "name" : "Beats slušalice", "image" : "/images/beats.jpg"
                },
                {
                    "name" : "Sony earphones", "image" : "/images/earphones.jpg"
                }
            ]
        },
        { 
            "name" : "CD-i i ploče",
            "image" : "speakers.jpg",
            "products" : [
                { 
                    "name" : "Haustor ploča", "image" : "/images/haustor.jpg"
                },
                {
                    "name" : "Led zeppelin CD", "image" : "/images/led.jpg"
                },
                {
                    "name" : "Aerodrom ploča", "image" : "/images/aerodrom.jpg"
                },
                {
                    "name" : "Rolling stones CD", "image" : "/images/stones.jpg"
                },
                {
                    "name" : "Beatles ploča", "image" : "/images/beatles.jpg"
                }
            ]
        },
        { 
            "name" : "Puhači instrumenti",
            "image" : "speakers.jpg",
            "products" : [
                { 
                    "name" : "Saksofon", "image" : "/images/sax.jpg"
                },
                {
                    "name" : "Flauta", "image" : "/images/flute.jpg"
                },
                {
                    "name" : "Pan flauta", "image" : "/images/pan-flute.jpg"
                },
                {
                    "name" : "Klarinet", "image" : "/images/clarinet.jpg"
                },
                {
                    "name" : "Truba", "image" : "/images/trumpet.jpg"
                }
            ]
        },
        { 
            "name" : "Gudački instrumenti",
            "image" : "speakers.jpg",
            "products" : [
                { 
                    "name" : "Violina", "image" : "/images/violina.jpg"
                },
                {
                    "name" : "Viola", "image" : "/images/viola.jpg"
                },
                {
                    "name" : "Violončelo", "image" : "/images/cello.jpg"
                },
                {
                    "name" : "Kontrabas", "image" : "/images/bass.jpg"
                },
                {
                    "name" : "Koncertna violina", "image" : "/images/concet-violin.jpg"
                }
            ]
        }
    ]
}

module.exports = data;