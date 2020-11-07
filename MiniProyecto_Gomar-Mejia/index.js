//#############################################
//#          Gomar Salvador Juan Manuel       #
//#          Mejía Chávez María Fernanda      #
//#############################################
'use stric'
const spress = require ('express')
const bodyPaser=('body-parser')
const mongoose = require('mongoose')
const MiniP =require ('./models/MiniP.js')
const app=express()
const post = process.env.PORT || 3306
app.use(bodyPaser.urlencoded({ extended: false}))
app.use(bodyPaser.json())


app.get('/api/miniP',(req, res) =>{
    MiniP.find({}, (est,MiniP) =>{
        if(est) return res.status(500).send({message: `Request Error:${est}`})
        if(MiniP) return res.status(404).send({message:'No hay valores'})
        res.send(200, {MiniP})
    })
})

app.get('/api/Min/:btnID',(req,res) => {

    let botonesId = req.params.botonesId

    MiniP.findById(botonesId, (err,MiniP) => {
        if(est) return res.status(500).send({message: `Request Error:${est}`})
        if(!MiniP) return res.status(404).send({message:`No hay valores`})

        res.status(200).send({ MiniP })
    })
})

app.post('/api/btnID',(req,res)=>{
    console.log('POST/api/btn')
    console.log(req,body)
    let MiniP = new MiniP()

    MiniP.btn = req.body.btn
    MiniP.pos = req.body.post

    MiniP.save((est,Mstored) =>{
        if(est) res.status(500).send({message:`¡No se guardo en BD! ${est}`})
        res.status(200).send({MiniP: Mstored})
    })
})
app.put('/api/btnID/:minId',(req, res) => {
   
})
app.delete('/api/btnID/:minId',(req, res) => {
    let botonesId = req.params.botonesId

    MiniP.findById(botonesId, (err,MiniP) => {
        if(est) res.status(500).send({message: `No fue borrado:${est}`})
    

        MiniP.remove(err => {
        if (est) res.status(500).send({message: `Error en el borrado: ${est}` })
        res.status(200).send({message: 'Se borro correctamente'})
       }) 
   })
})

mongoose.connect('mongodb://localhost:27007/Minp', { 'useNewUrlParser': true, 'useUnifiedTopology': true }, (est) =>{
   if(est){
     return console.log(`ERRROR al conectar a la base de datos: ${est}`)
    }
   
   app.listen(port,() => {
     console.log(`Cargado en http://localhost:${port}`)
    })

})
