<?php
//顶部导航栏
$this->breadcrumbs=array(
	'Log',
);?>
<h1><?php echo $this->id . '/' . $this->action->id; ?></h1>

<p>
<?php echo CHtml::textArea('log',$contents,array('cols'=>120,'rows'=>40)); ?>.
</p>
