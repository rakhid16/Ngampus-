const path = require('path')
const express = require('express')
const bodyParser = require('body-parser')
const app = express()

app.set('views', path.join(__dirname, 'views'))
app.set('view engine', 'hbs')
app.use(bodyParser.urlencoded({ extended: false }))
app.use(express.static(path.join(__dirname, 'public')))

app.get('/', (req, res) => {
  res.render('index', { name: 'zayd' })
})

app.get('/about', (req, res) => {
  res.send('halaman about')
})

app.get('/post', (req, res) => {
  res.render('form')
})

app.post('/post', (req, res) => {
  res.render('index', { name: req.body.textname })
})

app.listen(3000, () => {
  console.log('Server berjalan di http://localhost:3000')
})
