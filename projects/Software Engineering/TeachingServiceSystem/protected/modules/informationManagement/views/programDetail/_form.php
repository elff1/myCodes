<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'program-detail-form',
	'enableAjaxValidation'=>false,
)); ?>

	<p class="note"><?php
	echo InformationManagementModule::t('other','Fields with <span class="required">*</span> are required.'); /* no CHtml::encode here*/?></p>

	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'course_id'); ?>
		<?php echo $form->textField($model,'course_id',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'course_id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'type'); ?>
		<?php echo $form->textField($model,'type'); ?>
		<?php echo $form->error($model,'type'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'required'); ?>
		<?php echo $form->textField($model,'required'); ?>
		<?php echo $form->error($model,'required'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'recommended_year'); ?>
		<?php echo $form->textField($model,'recommended_year'); ?>
		<?php echo $form->error($model,'recommended_year'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'recommended_term'); ?>
		<?php echo $form->textField($model,'recommended_term'); ?>
		<?php echo $form->error($model,'recommended_term'); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? Yii::t('base','Create'):Yii::t('base','Save')); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->