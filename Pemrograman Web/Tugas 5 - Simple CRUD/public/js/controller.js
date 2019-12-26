$(document).ready(function(){

  // TAMBAH DATA
  $('#mytable').on('click','.edit',function(){
    var nrp = $(this).data('nrp')
    var nama = $(this).data('nama')
    var alamat = $(this).data('alamat')
    var jenis_kelamin = $(this).data('jenis_kelamin')

    // EDIT DATA
    $('#EditModal').modal('show')
    $('.nrp').val(nrp)
    $('.nama').val(nama)
    $('.alamat').val(alamat)
    $('.jenis_kelamin').val(jenis_kelamin)
  })
  
  // HAPUS DATA
  $('#mytable').on('click','.delete',function(){
    var nrp = $(this).data('nrp')
    $('#DeleteModal').modal('show')
    $('.nrp2').val(nrp)
  })
})