<!DOCTYPE html>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="shortcut icon" type="image/png" href="/wahid/main/favicon.png"/>
    <link rel="stylesheet" href="/wahid/main/0.css" />
    <title>Wahid in a NutShell</title>
  </head>
<body>


  <!-- HERO IMAGE -->
  <div class="container">
    <div class="hero-image">  
      <div class="hero-text">
        <h1 style="font-size:50px">Hello <span></span></h1>
        <p>Want to know how deep the rabbit hole goes?</p><br>
        <button><a onclick="window.open('#about', '_self')">Let's see</a></button>
      </div>   
    </div>

    <!-- NAVIGATION BAR -->
    <header>
      <img src="/wahid/main/favicon.png" height=40 width=40>
        <ul>
          <li><a href="#about">About</a></li>
          <li><a href="#socpro">Social Project</a></li>
          <li><a href="#journ">Journey</a></li>
          <li><a href="#expert">Expertise</a></li>
          <li><a onclick="window.open('/wahid/second/index.html', '_self')">Costumize</a></li>
        </ul>
    </header>

  <!-- ABOUT ME -->
  <div class="about-me" id="about">
    <div class="about-me-img">
      <img src="/wahid/main/me.png" alt="Avatar"> 
    </div> 
    <div class="about-me-txt">
      <h1>About me</h1>
      <p>Hi! My name is <?php echo $_POST['name'] ?>.<br>
        Was born in <?php echo $_POST['brithPlc'] ?>, <?php echo $_POST['brithdate'] ?>.<br>
        I'm a undergraduate student in <?php echo $_POST['univ'] ?>.<br>
        Interested in <?php echo $_POST['exp1'] ?>, <?php echo $_POST['exp2'] ?> and Islamic Education as well.<br> 
        Would really love to explore the combination of research into <?php echo $_POST['exp3'] ?>.</p>
    </div>
  </div>

  <!-- MY SOCIAL PROJECTS -->
  <div id="socpro"></div>
  <hr style="width:0%;">
  <hr style="width:0%;">
  <hr style="width:0%;">
  <div class="sub-heading">
    <center>My Social Projects :</center>
    <hr style="width:25%; color: whitesmoke">
  </div>
  <div class="soc-projects">
    <div>
        <p><?php echo $_POST['sospro1'] ?></p>
      <img src="/wahid/main/quran.png" width="190" height="170">
      <p>Islam is the coolest way of life.<br>
      You can find peace in Islam by reading the quran.<br>
    Start your Quran journey here! </p>
    </div>
    <div>
        <p><?php echo $_POST['sospro2'] ?></p>
      <img src="/wahid/main/gnulinux.png" width="180" height="190">
      <p>Everyone can do some cool stuff in their<br>
        computer with non-proprietary Software.<br>
      Let's move on to GNU/Linux!</p>
    </div>
  </div>
  
  <!-- MY JOURNEY -->
  <div class="journey" id="journ">
    <!-- JOMBANG -->
    <div class="journey-jmbg">
      <div class="journey-jmbg-text">
        <h1><?php echo $_POST['ct1'] ?> - <i>where it all began</i></h1>
        <p><?php echo $_POST['ct1org1'] ?><br>
        <?php echo $_POST['ct1org2'] ?><br>
      <?php echo $_POST['ct1org3'] ?><br><br>
    Best moments in life and lesson to!</p>
      </div>
      <div class="journey-jmbg-img">
        <img src="/wahid/main/jmbg.png" width="350">
      </div>
    </div>

    <!-- SURABAYA -->
    <div class="journey-sby">
      <div class="journey-sby-img">
        <img src="/wahid/main/sby.png" height="250" width="250">
      </div>
      <div class="journey-sby-text">
        <h1><?php echo $_POST['ct2'] ?> - <i>there and back again</i></h1>
        <p><?php echo $_POST['ct2org1'] ?><br>
        <?php echo $_POST['ct2org2'] ?><br>
      <?php echo $_POST['ct2org3'] ?><br><br>
      just go forth and aim for the Jannah!</p>
      </div>
    </div>
  
    <!-- ? -->
    <div class="journey-idk">
      <div class="journey-idk-text">
          <h1>? - <i>let's take this further</i></h1>
          <p>So much has been done, exclaimed the soul of Frankenstein.<br><br>
          Where we will go?</p>
      </div>
      <div class="journey-idk-img" >
        <img src="/wahid/main/map.png" height="250" width="300">
      </div>
    </div>
  </div>

  <!-- MY EXPERTISE -->
  <div class="expert" id="expert">
    <center>My expertise :</center><br>
    <div>
      <img src="/wahid/main/SE.svg" width="275" height="212.5">
      <p><?php echo $_POST['exp1'] ?></p>
    </div>
    <div>
        <img src="/wahid/main/AI.svg" width="275" height="212.5">
      <p><?php echo $_POST['exp2'] ?></p>
    </div>
    <div>
    <img src="/wahid/main/DS.svg" width="275" height="212.5">
    <p><?php echo $_POST['exp3'] ?></p>
    </div>
  </div> 
  
  <!-- FOOTER -->
  <div class="footer">
    <div class="footer-credit">
        <b>Made with ambition by <?php echo $_POST['name'] ?></b>
    </div>
    <div class="footer-socmed">
      <a href="https://github.com/rakhid16" target="blank"><img src="/wahid/main/github.png" width="25" height="25"/></a>&nbsp;
      <a href="https://t.me/rakhmanWahid" target="blank"><img src="/wahid/main/tele.png" width="25" height="25"/></a>&nbsp;
      <a href="https://fb.com/radical.rakhman" target="blank"><img src="/wahid/main/fb.png" width="25" height="25"/></a>&nbsp;
      <a href="https://linkedin.com/in/rakhid16" target="blank"><img src="/wahid/main/in.png" width="25" height="25" /></a>
    </div> <div class="clear"></div>
  </div>
</div>
</body>
</html>