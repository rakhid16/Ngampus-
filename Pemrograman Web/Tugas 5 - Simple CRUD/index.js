const path = require('path')
const express = require('express')
const bodyParser = require('body-parser')
const mysql = require('mysql')

const app = express()
const connection = mysql.createConnection({
  host: 'localhost',
  user: 'root',
  password: '',
  database: 'crud_mhs',
})

connection.connect((error) => {
  if (error) throw error
  console.log('Database tersambung')
})

app.set('views', path.join(__dirname, 'views'))
app.set('view engine', 'hbs')
app.use(bodyParser.json())
app.use(bodyParser.urlencoded({ extended: false }))
app.use('/assets', express.static(path.join(__dirname, 'public')))

app.get('/', (request, response) => {
  connection.query('SELECT * FROM mhs', (error, results) => {
    if (error) throw error
    response.render('tampilan', { results })
  })
})

app.post('/save', (request, response) => {
  const student = {
    nrp: request.body.nrp,
    nama: request.body.nama,
    jenis_kelamin: request.body.jenis_kelamin,
    alamat: request.body.alamat,
  }

  connection.query('INSERT INTO mhs SET ?', student, (error) => {
    if (error) throw error
    response.redirect('/')
  })
})

app.post('/update', (request, response) => {
  const { nama, jenis_kelamin, alamat, nrp } = request.body
  const query =
    'UPDATE mhs SET nama = ?, jenis_kelamin = ?, alamat = ? WHERE nrp = ?'

  connection.query(query, [nama, jenis_kelamin, alamat, nrp], (error) => {
    if (error) throw error
    response.redirect('/')
  })
})

app.post('/delete', (request, response) => {
  connection.query(
    'DELETE FROM mhs WHERE nrp = ?',
    [request.body.nrp],
    (error) => {
      if (error) throw error
      response.redirect('/')
    },
  )
})

app.listen(3000, () => {
  console.log('Server berjalan di http://localhost:3000')
})
