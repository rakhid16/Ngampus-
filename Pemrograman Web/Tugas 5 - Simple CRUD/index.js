// FUNGSINYA SEPERTI import PADA PYTHON DAN #include PADA C
// const AGAR ISI DARI VARIABEL'NYA KONSTAN/TETAP/TIDAK BERUBAH
const hbs = require('hbs')
const path = require('path')
const mysql = require('mysql')
const express = require('express')
const bodyParser = require('body-parser')
const app = express()

// KONFIGURASI KONEKSI DENGAN DATABASE
const conn = mysql.createConnection({
  host: 'localhost',
  user: 'root',
  password: '',
  database: 'crud_mhs'
})
 
// SAMBUNGKAN DENGAN DATABASE
conn.connect((err) =>{
  if(err) throw err
  console.log('Database tersambung')
})
 
// ATUR MIDDLEWARE
app.set('views',path.join(__dirname,'views'))
app.set('view engine', 'hbs')
app.use(bodyParser.json())
app.use(bodyParser.urlencoded({ extended: false }))
app.use('/assets',express.static(__dirname + '/public'))
 
// ROUTING UNTUK MENAMPILKAN LAMAN UTAMA - SEMUA DATA
app.get('/',(req, res) => {
  let sql = "SELECT * FROM mhs"
  let query = conn.query(sql, (err, results) => {
    if(err) throw err
    res.render('tampilan',{
      results: results
    })
  })
})
 
// ROUTING UNTUK SIMPAN DATA
app.post('/save',(req, res) => {
  let data = {nrp: req.body.nrp, nama: req.body.nama, jenis_kelamin: req.body.jenis_kelamin, alamat: req.body.alamat}
  let sql = "INSERT INTO mhs SET ?"
  let query = conn.query(sql, data,(err, results) => {
    if(err) throw err
    res.redirect('/')
  })
})
 
// ROUTING UNTUK UBAH DATA
app.post('/update',(req, res) => {
  let sql = "UPDATE mhs SET nama='"+req.body.nama+"', jenis_kelamin='"+req.body.jenis_kelamin+"', alamat='"+req.body.alamat+"' WHERE nrp="+req.body.nrp
  let query = conn.query(sql, (err, results) => {
    if(err) throw err
    res.redirect('/')
  })
})
 
// ROUTING UNTUK HAPUS DATA
app.post('/delete',(req, res) => {
  let sql = "DELETE FROM mhs WHERE nrp="+req.body.nrp+""
  let query = conn.query(sql, (err, results) => {
    if(err) throw err
    res.redirect('/')
  })
})
 
// ATUR PORT SERVER
app.listen(3000, () => {
  console.log('Server sedang berjalan pada port 3000 - http://localhost:3000')
})