<?php
$this->breadcrumbs=array(
	$this->module->id,
);
?>
<h1><?php echo $this->uniqueId . '/' . $this->action->id; ?></h1>

<p>
This is the view content for action "<?php echo $this->action->id; ?>".
The action belongs to the controller "<?php echo get_class($this); ?>"
in the "<?php echo $this->module->id; ?>" module.
</p>
<p>
<div class="container" id="mainmenu">
<?php $this->widget('zii.widgets.CMenu',array(
			'items'=>array(
				array('label'=>'Student',
				'url'=>array('/site/index')),
				array('label'=>'Professor',
				'url'=>array('/site/index'),
				),
				array('label'=>'SuperAdmin',
				'url'=>array('/site/index'),
				),
				array('label'=>'Admin',
				'url'=>array('/site/index'),
				),
				)
			));
?>
</div>
</p>
<p>
You may customize this page by editing <tt><?php echo __FILE__; ?></tt>
</p>