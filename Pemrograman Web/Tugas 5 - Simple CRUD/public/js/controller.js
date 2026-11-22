$(document).ready(() => {
  $('#mytable').on('click', '.edit', function () {
    const nrp = $(this).data('nrp')
    const nama = $(this).data('nama')
    const alamat = $(this).data('alamat')
    const jenisKelamin = $(this).data('jenis_kelamin')

    $('#EditModal').modal('show')
    $('.nrp').val(nrp)
    $('.nama').val(nama)
    $('.alamat').val(alamat)
    $('.jenis_kelamin').val(jenisKelamin)
  })

  $('#mytable').on('click', '.delete', function () {
    const nrp = $(this).data('nrp')
    $('#DeleteModal').modal('show')
    $('.nrp2').val(nrp)
  })
})