// Semacam import di Python dan #include di C
const path = require('path')
const express = require('express')
const hbs = require('hbs')
const bodyParser = require('body-parser')
const app = express()

// MIDDLEWARE YANG DIGUNAKAN
app.set('views', path.join(__dirname, 'views'))
app.set('view engine', 'hbs')

app.use(bodyParser.urlencoded({ extended: false }))
app.use(express.static('public'))

// ROUTING BIASA
app.get('/', (req, res) => {
    res.render('index',{
        name : "zayd"
    })
})

app.get('/about',(req, res) => {
    res.send('halaman about')
  })

app.get('/post', (req,res) => {
    res.render('form')
})

app.post('/post', (req, res) => {
    res.render('index', {
        name : req.body.textname
    })
})

// ALAMAT SERVER - MEMBUKA AKSES KE http://localhost:3000
app.listen(3000, () =>{
    console.log('Server is running at port 3000')
})
